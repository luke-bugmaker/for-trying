// Terminal Ping Pong — first-person table tennis in the terminal.
//
// Move the mouse to steer your racket (position AND swing speed); how fast
// you're moving the racket at the moment of contact determines the power
// and direction of your return. Note: the racket tracks the cursor
// continuously (no need to hold a button down) — this felt more natural
// for a fast-reaction game than requiring a click-drag; see the comment
// near setupTerminal() if you'd rather require holding a button.
//
// Two modes, chosen at startup:
//   1) Practice wall — the far end always returns the ball (forgiving)
//   2) AI opponent   — a simple paddle tracks the ball and can miss
//
// Compile: g++ -O2 -o pingpong terminal_pingpong.cpp
// Run:     ./pingpong
// Ctrl+C to quit.
//
// TUNING: the constants marked "tunable" below control feel (serve speed,
// gravity, bounce energy, hit zone size). These are a first-pass starting
// point — expect to nudge them once you can actually play it.

#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <csignal>
#include <ctime>
#include <vector>
#include <string>
#include <algorithm>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

// ---------- world / view constants ----------
const int   W = 90, H = 34;
const float SCALE_X = 55.0f, SCALE_Y = 30.0f;

const float TABLE_HALF_W = 1.4f;
const float TABLE_LEN    = 8.0f;
const float NET_Z        = TABLE_LEN / 2.0f;
const float NET_H        = 0.45f;

const float EYE_Y = 1.15f;   // eye height above table surface
const float EYE_Z = -0.7f;   // stand a bit behind own end of table

// tunable: gameplay feel
const float GRAVITY   = -9.0f;
const float RESTITUTE = 0.78f;   // energy kept after a table bounce
const float BALL_R    = 0.10f;
const float RACKET_R  = 0.34f;
const float RACKET_Z  = 0.15f;   // how far in front of the eye the racket sits
const float OPP_Z     = TABLE_LEN - 0.5f;
const float AI_R      = 0.55f;
const float AI_SPEED  = 3.2f;    // max AI paddle speed, units/sec
const float SERVE_VZ  = -3.4f;   // horizontal serve speed (tunable: game pace)
const float SERVE_VY  = 1.2f;    // serve toss speed (tunable: arc height)

enum Mode { MODE_WALL, MODE_AI };

struct Vec3 { float x, y, z; };
struct Point2D { int x, y; bool valid; };

Vec3 sub(Vec3 a, Vec3 b) { return { a.x - b.x, a.y - b.y, a.z - b.z }; }

Point2D project(Vec3 world, Vec3 eye) {
    Vec3 r = sub(world, eye);
    if (r.z < 0.05f) return { 0, 0, false }; // behind camera, don't draw
    float ooz = 1.0f / r.z;
    int sx = W / 2 + (int)(SCALE_X * r.x * ooz);
    int sy = H / 2 - (int)(SCALE_Y * r.y * ooz);
    return { sx, sy, true };
}

char screen[H][W];

void putc_safe(int x, int y, char c) {
    if (x >= 0 && x < W && y >= 0 && y < H) screen[y][x] = c;
}

void drawBlob(int cx, int cy, char c) {
    putc_safe(cx, cy, c);
    putc_safe(cx + 1, cy, c); putc_safe(cx - 1, cy, c);
    putc_safe(cx, cy + 1, c); putc_safe(cx, cy - 1, c);
}

void fillQuad(Point2D p[4], char c) {
    for (int i = 0; i < 4; i++) if (!p[i].valid) return;
    int minY = H, maxY = 0;
    for (int i = 0; i < 4; i++) { minY = std::min(minY, p[i].y); maxY = std::max(maxY, p[i].y); }
    minY = std::max(minY, 0); maxY = std::min(maxY, H - 1);
    for (int y = minY; y <= maxY; y++) {
        std::vector<int> xs;
        for (int i = 0; i < 4; i++) {
            Point2D a = p[i], b = p[(i + 1) % 4];
            if (a.y == b.y) continue;
            if ((y >= a.y && y < b.y) || (y >= b.y && y < a.y)) {
                float t = (float)(y - a.y) / (b.y - a.y);
                xs.push_back((int)(a.x + t * (b.x - a.x)));
            }
        }
        if (xs.size() < 2) continue;
        std::sort(xs.begin(), xs.end());
        for (int x = std::max(xs.front(), 0); x <= std::min(xs.back(), W - 1); x++) screen[y][x] = c;
    }
}

// ---------- terminal / mouse (ANSI escapes, same family as the cube demo) ----------
struct termios orig_termios;
void restoreTerminal() {
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
    printf("\x1b[?1000l\x1b[?1002l\x1b[?1006l\x1b[?25h");
    fflush(stdout);
}
void handleSignal(int) { restoreTerminal(); exit(0); }
void setupTerminal() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    raw.c_cc[VMIN] = 0; raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
    // Click-and-drag racket control (same mouse mode as the cube demo) —
    // hold the left mouse button and move it to steer the racket.
    printf("\x1b[?1000h\x1b[?1002h\x1b[?1006h\x1b[?25l\x1b[2J");
    fflush(stdout);
    signal(SIGINT, handleSignal);
    atexit(restoreTerminal);
}

std::string inputBuf;
bool dragging = false;
int mouseX = 0, mouseY = 0;

void pollMouse() {
    char buf[256]; ssize_t n;
    while ((n = read(STDIN_FILENO, buf, sizeof(buf))) > 0) inputBuf.append(buf, n);
    size_t pos;
    while ((pos = inputBuf.find("\x1b[<")) != std::string::npos) {
        size_t end = inputBuf.find_first_of("Mm", pos);
        if (end == std::string::npos) break;
        std::string seq = inputBuf.substr(pos + 3, end - pos - 3);
        char type = inputBuf[end];
        inputBuf.erase(0, end + 1);
        int cb, cx, cy;
        if (sscanf(seq.c_str(), "%d;%d;%d", &cb, &cx, &cy) == 3) {
            mouseX = cx; mouseY = cy;
            dragging = (type == 'M'); // 'M' = pressed/dragging, 'm' = released
        }
    }
}

void mouseToRacket(float &rx, float &ry) {
    rx = ((float)mouseX / W - 0.5f) * (TABLE_HALF_W * 2.6f);
    ry = (1.0f - (float)mouseY / H) * 1.6f;
    if (rx < -2.2f) rx = -2.2f;
    if (rx > 2.2f) rx = 2.2f;
    if (ry < -0.3f) ry = -0.3f;
    if (ry > 1.8f) ry = 1.8f;
}

// ---------- game state ----------
struct Ball { Vec3 pos, vel; };

void serveBall(Ball &b, unsigned &seed) {
    // Ball starts on the opponent's half already in flight toward the
    // player, as if just served/returned from the far end.
    float jitter = ((rand_r(&seed) % 100) / 100.0f - 0.5f) * 1.0f;
    b.pos = { jitter, 0.9f, OPP_Z - 0.3f };
    b.vel = { -jitter * 0.6f, SERVE_VY, SERVE_VZ };
}

int main() {
    printf("Terminal Ping Pong\n");
    printf("  1) Practice wall (always returns the ball)\n");
    printf("  2) AI opponent (can miss)\n");
    printf("Choose 1 or 2: ");
    fflush(stdout);
    int choice = getchar();
    Mode mode = (choice == '2') ? MODE_AI : MODE_WALL;

    setupTerminal();

    Vec3 eye = { 0, EYE_Y, EYE_Z };
    unsigned seed = (unsigned)time(nullptr);

    Ball ball;
    serveBall(ball, seed);

    float racketX = 0, racketY = 0.8f, prevRacketX = racketX, prevRacketY = racketY;
    float aiX = 0, aiY = 0.8f;

    int rally = 0, bestRally = 0, resets = 0;
    const float DT = 1.0f / 60.0f;

    while (true) {
        pollMouse();
        if (dragging) mouseToRacket(racketX, racketY);
        float racketVX = (racketX - prevRacketX) / DT;
        float racketVY = (racketY - prevRacketY) / DT;
        prevRacketX = racketX; prevRacketY = racketY;

        // ---- physics step ----
        ball.vel.y += GRAVITY * DT;
        ball.pos.x += ball.vel.x * DT;
        ball.pos.y += ball.vel.y * DT;
        ball.pos.z += ball.vel.z * DT;

        // table bounce
        if (ball.pos.y <= BALL_R && ball.vel.y < 0 &&
            fabsf(ball.pos.x) <= TABLE_HALF_W && ball.pos.z >= 0 && ball.pos.z <= TABLE_LEN) {
            ball.pos.y = BALL_R;
            ball.vel.y = -ball.vel.y * RESTITUTE;
        } else if (ball.pos.y <= 0.0f && ball.vel.y < 0) {
            resets++; rally = 0;
            serveBall(ball, seed);
        }

        // net
        if (fabsf(ball.pos.z - NET_Z) < 0.08f && ball.pos.y < NET_H) {
            resets++; rally = 0;
            serveBall(ball, seed);
        }

        // player racket — vel.z < 0 (approaching player) prevents re-triggering
        // on the same pass, since a successful hit flips vel.z positive.
        if (ball.vel.z < 0 && fabsf(ball.pos.z - RACKET_Z) < 0.25f) {
            float dx = ball.pos.x - racketX, dy = ball.pos.y - racketY;
            if (dx * dx + dy * dy < RACKET_R * RACKET_R) {
                ball.vel.z = fabsf(ball.vel.z) * 1.05f;
                ball.vel.x += racketVX * 0.5f;
                ball.vel.y = fabsf(ball.vel.y) * 0.6f + racketVY * 0.5f + 1.0f;
                rally++; bestRally = std::max(bestRally, rally);
            }
        }

        // opponent end
        if (ball.vel.z > 0 && ball.pos.z >= OPP_Z) {
            if (mode == MODE_WALL) {
                ball.vel.z = -fabsf(ball.vel.z);
                ball.vel.x = ((rand_r(&seed) % 100) / 100.0f - 0.5f) * 1.5f;
                ball.vel.y = fabsf(ball.vel.y) * 0.5f + 1.5f;
            } else {
                float dx = ball.pos.x - aiX;
                float maxStep = AI_SPEED * DT;
                if (dx > maxStep) aiX += maxStep; else if (dx < -maxStep) aiX -= maxStep; else aiX = ball.pos.x;

                float ddx = ball.pos.x - aiX, ddy = ball.pos.y - aiY;
                if (ddx * ddx + ddy * ddy < AI_R * AI_R) {
                    ball.vel.z = -fabsf(ball.vel.z);
                    ball.vel.x = -ddx * 1.2f;
                    ball.vel.y = fabsf(ball.vel.y) * 0.5f + 1.2f;
                } else {
                    resets++; rally = 0; // AI whiffed — point for you
                    serveBall(ball, seed);
                }
            }
        }

        // ball got past the player entirely
        if (ball.pos.z < EYE_Z) {
            resets++; rally = 0;
            serveBall(ball, seed);
        }

        // ---- render ----
        memset(screen, ' ', sizeof(screen));

        Point2D tbl[4] = {
            project({-TABLE_HALF_W, 0, 0}, eye), project({TABLE_HALF_W, 0, 0}, eye),
            project({TABLE_HALF_W, 0, TABLE_LEN}, eye), project({-TABLE_HALF_W, 0, TABLE_LEN}, eye)
        };
        fillQuad(tbl, '.');

        Point2D net[4] = {
            project({-TABLE_HALF_W, 0, NET_Z}, eye), project({TABLE_HALF_W, 0, NET_Z}, eye),
            project({TABLE_HALF_W, NET_H, NET_Z}, eye), project({-TABLE_HALF_W, NET_H, NET_Z}, eye)
        };
        fillQuad(net, '#');

        Point2D oppP = project({ (mode == MODE_AI ? aiX : 0), 0.8f, OPP_Z }, eye);
        if (oppP.valid) drawBlob(oppP.x, oppP.y, mode == MODE_AI ? 'A' : '=');

        Point2D racketP = project({racketX, racketY, RACKET_Z}, eye);
        if (racketP.valid) drawBlob(racketP.x, racketP.y, 'O');

        Point2D shadow = project({ball.pos.x, 0.01f, ball.pos.z}, eye);
        if (shadow.valid) putc_safe(shadow.x, shadow.y, ',');
        Point2D ballP = project(ball.pos, eye);
        if (ballP.valid) putc_safe(ballP.x, ballP.y, '@');

        printf("\x1b[H");
        for (int y = 0; y < H; y++) { fwrite(screen[y], 1, W, stdout); putchar('\n'); }
        printf("Rally: %d   Best: %d   Resets: %d   (mode: %s)   Ctrl+C to quit\n",
               rally, bestRally, resets, mode == MODE_WALL ? "wall" : "AI");
        printf("[debug] drag:%s mouseRaw:(%d,%d) racket:(%.2f,%.2f) ball:(%.2f,%.2f,%.2f)   \n",
               dragging ? "Y" : "N", mouseX, mouseY, racketX, racketY, ball.pos.x, ball.pos.y, ball.pos.z);
        fflush(stdout);

        usleep(16000);
    }
}
