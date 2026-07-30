// Interactive ASCII cube — drag with the left mouse button to rotate it,
// release mid-drag and it keeps spinning with momentum (friction slows it down).
//
// Cross-platform (Linux/macOS/WSL) version: uses ANSI/xterm mouse reporting
// instead of a Windows-only console API, so this also works over SSH.
//
// Same math as before: rotate geometry each frame, project to 2D, shade by
// surface normal vs light direction. A cube is convex, so backface culling
// (skip faces pointing away from the camera) replaces a full z-buffer, and
// visible faces are drawn back-to-front (painter's algorithm).
//
// Compile:
//   g++ -O2 -o cube interactive_cube.cpp
// Run (in a real terminal, local or over SSH):
//   ./cube
// Click and drag with the left mouse button. Ctrl+C to quit.

#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <csignal>
#include <vector>
#include <string>
#include <algorithm>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

const int W = 80, H = 30;
const float SCALE = 40.0f;
const float DIST = 5.0f;

struct Vec3 { float x, y, z; };

Vec3 rotate(Vec3 v, float pitch, float yaw) {
    float x1 = v.x * cosf(yaw) + v.z * sinf(yaw);
    float z1 = -v.x * sinf(yaw) + v.z * cosf(yaw);
    float y2 = v.y * cosf(pitch) - z1 * sinf(pitch);
    float z2 = v.y * sinf(pitch) + z1 * cosf(pitch);
    return { x1, y2, z2 };
}

struct Point2D { int x, y; };

Point2D project(Vec3 v) {
    float z = v.z + DIST;
    float ooz = 1.0f / z;
    int sx = (int)(W / 2 + SCALE * v.x * ooz);
    int sy = (int)(H / 2 - SCALE * 0.5f * v.y * ooz);
    return { sx, sy };
}

Vec3 vertices[8] = {
    {-1,-1,-1}, {1,-1,-1}, {1,1,-1}, {-1,1,-1},
    {-1,-1, 1}, {1,-1, 1}, {1,1, 1}, {-1,1, 1}
};

int faces[6][4] = {
    {0,1,2,3}, {5,4,7,6}, {4,0,3,7}, {1,5,6,2}, {3,2,6,7}, {4,5,1,0}
};

Vec3 faceNormals[6] = {
    {0,0,-1}, {0,0,1}, {-1,0,0}, {1,0,0}, {0,1,0}, {0,-1,0}
};

char screen[H][W];

void fillPolygon(Point2D pts[4], char ch) {
    int minY = H, maxY = 0;
    for (int i = 0; i < 4; i++) { minY = std::min(minY, pts[i].y); maxY = std::max(maxY, pts[i].y); }
    minY = std::max(minY, 0); maxY = std::min(maxY, H - 1);

    for (int y = minY; y <= maxY; y++) {
        std::vector<int> xs;
        for (int i = 0; i < 4; i++) {
            Point2D a = pts[i], b = pts[(i + 1) % 4];
            if (a.y == b.y) continue;
            if ((y >= a.y && y < b.y) || (y >= b.y && y < a.y)) {
                float t = (float)(y - a.y) / (b.y - a.y);
                xs.push_back((int)(a.x + t * (b.x - a.x)));
            }
        }
        if (xs.size() < 2) continue;
        std::sort(xs.begin(), xs.end());
        for (int x = std::max(xs.front(), 0); x <= std::min(xs.back(), W - 1); x++) {
            screen[y][x] = ch;
        }
    }
}

// --- terminal / mouse handling (ANSI escape sequences, works locally and over SSH) ---
struct termios orig_termios;

void restoreTerminal() {
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
    printf("\x1b[?1000l\x1b[?1002l\x1b[?1006l\x1b[?25h"); // disable mouse reporting, show cursor
    fflush(stdout);
}

void handleSignal(int) {
    restoreTerminal();
    exit(0);
}

void setupTerminal() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);

    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

    printf("\x1b[?1000h\x1b[?1002h\x1b[?1006h\x1b[?25l"); // enable button+motion mouse reporting, hide cursor
    fflush(stdout);

    signal(SIGINT, handleSignal);
    atexit(restoreTerminal);
}

std::string inputBuf;

void pollMouseEvents(float& yaw, float& pitch, float& velYaw, float& velPitch,
                      bool& dragging, int& lastX, int& lastY) {
    char buf[256];
    ssize_t n;
    while ((n = read(STDIN_FILENO, buf, sizeof(buf))) > 0) {
        inputBuf.append(buf, n);
    }

    size_t pos;
    while ((pos = inputBuf.find("\x1b[<")) != std::string::npos) {
        size_t end = inputBuf.find_first_of("Mm", pos);
        if (end == std::string::npos) break; // incomplete sequence, wait for more bytes
        std::string seq = inputBuf.substr(pos + 3, end - pos - 3);
        char type = inputBuf[end];
        inputBuf.erase(0, end + 1);

        int cb, cx, cy;
        if (sscanf(seq.c_str(), "%d;%d;%d", &cb, &cx, &cy) == 3) {
            if (type == 'M') { // press, or motion while a button is held
                if (dragging) {
                    int dx = cx - lastX;
                    int dy = cy - lastY;
                    velYaw = dx * 0.05f;
                    velPitch = dy * 0.05f;
                    yaw += velYaw;
                    pitch += velPitch;
                }
                dragging = true;
                lastX = cx;
                lastY = cy;
            } else { // 'm' = release
                dragging = false;
            }
        }
    }
}

int main() {
    setupTerminal();

    float pitch = 0.3f, yaw = 0.5f;
    float velPitch = 0, velYaw = 0;
    bool dragging = false;
    int lastX = 0, lastY = 0;

    const char shades[] = " .:-=+*#%@";
    const Vec3 light = {0.4f, 0.6f, -1.0f};

    while (true) {
        pollMouseEvents(yaw, pitch, velYaw, velPitch, dragging, lastX, lastY);

        if (!dragging) {
            yaw += velYaw;
            pitch += velPitch;
            velYaw *= 0.95f;
            velPitch *= 0.95f;
        }

        memset(screen, ' ', sizeof(screen));

        struct FaceDraw { float depth; Point2D pts[4]; char ch; };
        std::vector<FaceDraw> drawList;

        for (int f = 0; f < 6; f++) {
            Vec3 n = rotate(faceNormals[f], pitch, yaw);
            if (n.z >= 0) continue;

            Point2D pts[4];
            float depth = 0;
            for (int i = 0; i < 4; i++) {
                Vec3 v = rotate(vertices[faces[f][i]], pitch, yaw);
                pts[i] = project(v);
                depth += v.z;
            }
            depth /= 4;

            float lightDot = n.x * light.x + n.y * light.y + n.z * light.z;
            int shadeIdx = (int)((lightDot + 1.0f) / 2.0f * 9);
            shadeIdx = std::max(0, std::min(9, shadeIdx));

            drawList.push_back({ depth, { pts[0], pts[1], pts[2], pts[3] }, shades[shadeIdx] });
        }

        std::sort(drawList.begin(), drawList.end(), [](const FaceDraw& a, const FaceDraw& b) {
            return a.depth > b.depth;
        });
        for (auto& fd : drawList) fillPolygon(fd.pts, fd.ch);

        printf("\x1b[H"); // cursor home (avoids flicker vs clearing the whole screen)
        for (int y = 0; y < H; y++) {
            fwrite(screen[y], 1, W, stdout);
            putchar('\n');
        }
        fflush(stdout);

        usleep(16000); // ~60 fps
    }

    return 0;
}
