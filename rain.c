/*
compile w/ gcc
ctrl + c to quit
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <math.h>

#define W 80
#define H 24
#define FRAME_MS 50

static volatile sig_atomic_t running = 1;
static void stop(int s) { (void)s; running = 0; }

static char glyph(void) { return (char)(33 + rand() % 94); }

int main(void)
{
    char grid[H][W];
    int head[W], len[W];
    long frame = 0;

    system("");
    signal(SIGINT, stop);
    srand((unsigned)time(NULL));

    for (int x = 0; x < W; x++) {
        head[x] = -(rand() % H);
        len[x]  = 5 + rand() % 15;
        for (int y = 0; y < H; y++) grid[y][x] = glyph();
    }

    printf("\x1b[2J\x1b[?25l");

    while (running) {
        printf("\x1b[H");

        for (int y = 0; y < H; y++) {
            for (int x = 0; x < W; x++) {
                int d = head[x] - y;
                if (d >= 0 && d < len[x]) {
                    if (rand() % 8 == 0) grid[y][x] = glyph();

                    if (d == 0) {
                        printf("\x1b[38;2;255;255;255m%c", grid[y][x]);
                    } else {
                        double b = 1.0 - (double)d / len[x];
                        double hue = (x + frame) * 0.12;
                        int r = (int)((sin(hue)        * 127 + 128) * b);
                        int g = (int)((sin(hue + 2.094) * 127 + 128) * b);
                        int bl = (int)((sin(hue + 4.188) * 127 + 128) * b);
                        printf("\x1b[38;2;%d;%d;%dm%c", r, g, bl, grid[y][x]);
                    }
                } else {
                    putchar(' ');
                }
            }
            if (y < H - 1) printf("\x1b[0m\n");
        }

        for (int x = 0; x < W; x++) {
            head[x]++;
            if (head[x] - len[x] > H) {
                head[x] = -(rand() % 10);
                len[x]  = 5 + rand() % 15;
            }
        }

        fflush(stdout);
        frame++;

        clock_t end = clock() + (CLOCKS_PER_SEC * FRAME_MS) / 1000;
        while (clock() < end) { }
    }

    printf("\x1b[0m\x1b[?25h\n");
    return 0;
}