// Interactive ASCII cube — drag with the left mouse button to rotate it,
// release mid-drag and it keeps spinning with momentum (friction slows it down).
//
// Builds on the same idea as the spinning donut: rotate geometry each frame,
// project to 2D, shade by surface normal vs light direction. Since a cube is
// convex, backface culling (skip faces pointing away from the camera) replaces
// the donut's per-pixel z-buffer, and visible faces are drawn back-to-front.
//
// Compile (MinGW / g++ on Windows):
//   g++ -O2 -o cube.exe interactive_cube.cpp
// Run in a real console window (cmd.exe or Windows Terminal):
//   cube.exe
// Click and drag with the left mouse button. Ctrl+C to quit.

#include <windows.h>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

const int W = 80, H = 30;
const float SCALE = 40.0f;
const float DIST = 5.0f; // distance of cube from camera along z

struct Vec3 { float x, y, z; };

// Rotate a point: yaw around Y axis, then pitch around X axis
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
    int sy = (int)(H / 2 - SCALE * 0.5f * v.y * ooz); // 0.5 corrects for character cell aspect ratio
    return { sx, sy };
}

Vec3 vertices[8] = {
    {-1,-1,-1}, {1,-1,-1}, {1,1,-1}, {-1,1,-1},
    {-1,-1, 1}, {1,-1, 1}, {1,1, 1}, {-1,1, 1}
};

int faces[6][4] = {
    {0,1,2,3}, // front  (z = -1)
    {5,4,7,6}, // back   (z = +1)
    {4,0,3,7}, // left   (x = -1)
    {1,5,6,2}, // right  (x = +1)
    {3,2,6,7}, // top    (y = +1)
    {4,5,1,0}  // bottom (y = -1)
};

Vec3 faceNormals[6] = {
    {0,0,-1}, {0,0,1}, {-1,0,0}, {1,0,0}, {0,1,0}, {0,-1,0}
};

char screen[H][W];

// Scanline fill for a 4-point polygon
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

int main() {
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD prevMode;
    GetConsoleMode(hIn, &prevMode);
    // ENABLE_EXTENDED_FLAGS without ENABLE_QUICK_EDIT_MODE turns off text-selection
    // capture so mouse drags reach the app instead of the console's own selection UI.
    SetConsoleMode(hIn, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);

    float pitch = 0.3f, yaw = 0.5f;
    float velPitch = 0, velYaw = 0;
    bool dragging = false;
    int lastX = 0, lastY = 0;

    const char shades[] = " .:-=+*#%@";
    const Vec3 light = {0.4f, 0.6f, -1.0f};

    while (true) {
        // --- drain pending mouse events ---
        DWORD events = 0;
        GetNumberOfConsoleInputEvents(hIn, &events);
        while (events-- > 0) {
            INPUT_RECORD rec;
            DWORD read;
            ReadConsoleInput(hIn, &rec, 1, &read);
            if (rec.EventType == MOUSE_EVENT) {
                MOUSE_EVENT_RECORD& m = rec.Event.MouseEvent;
                bool leftDown = m.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED;
                if (leftDown) {
                    if (dragging) {
                        int dx = m.dwMousePosition.X - lastX;
                        int dy = m.dwMousePosition.Y - lastY;
                        velYaw = dx * 0.05f;
                        velPitch = dy * 0.05f;
                        yaw += velYaw;
                        pitch += velPitch;
                    }
                    dragging = true;
                    lastX = m.dwMousePosition.X;
                    lastY = m.dwMousePosition.Y;
                } else {
                    dragging = false;
                }
            }
        }

        // momentum spin when not actively dragging
        if (!dragging) {
            yaw += velYaw;
            pitch += velPitch;
            velYaw *= 0.95f;
            velPitch *= 0.95f;
        }

        // --- build the frame ---
        memset(screen, ' ', sizeof(screen));

        struct FaceDraw { float depth; Point2D pts[4]; char ch; };
        std::vector<FaceDraw> drawList;

        for (int f = 0; f < 6; f++) {
            Vec3 n = rotate(faceNormals[f], pitch, yaw);
            if (n.z >= 0) continue; // backface cull: camera looks down +z, skip faces pointing away

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

        // painter's algorithm: draw farthest face first so nearer faces overwrite it
        std::sort(drawList.begin(), drawList.end(), [](const FaceDraw& a, const FaceDraw& b) {
            return a.depth > b.depth;
        });
        for (auto& fd : drawList) fillPolygon(fd.pts, fd.ch);

        // --- draw without clearing the screen (avoids flicker vs system("cls")) ---
        COORD topLeft = {0, 0};
        SetConsoleCursorPosition(hOut, topLeft);
        for (int y = 0; y < H; y++) {
            fwrite(screen[y], 1, W, stdout);
            putchar('\n');
        }

        Sleep(16); // ~60 fps
    }

    SetConsoleMode(hIn, prevMode);
    return 0;
}
