#ifndef SCREEN_H
#define SCREEN_H

#include <stdio.h>

#define ESC "\033"
#define RESET ESC "[0m"
#define BOLD ESC "[1m"
#define ITALIC ESC "[3m"
#define BLINK ESC "[5m"
#define REVERSE ESC "[7m"
#define CLEARSCREEN ESC "[2J"
#define HOMECURSOR ESC "[H"
#define HIDECURSOR ESC "[?25l"
#define SHOWCURSOR ESC "[?25h"

#define BLACK ESC "[30m"
#define RED ESC "[31m"
#define GREEN ESC "[32m"
#define YELLOW ESC "[33m"
#define BLUE ESC "[34m"
#define MAGENTA ESC "[35m"
#define CYAN ESC "[36m"
#define WHITE ESC "[37m"
#define DARKGRAY ESC "[90m"
#define LIGHTGRAY ESC "[97m"

typedef enum
{
    COLOR_BLACK,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_YELLOW,
    COLOR_BLUE,
    COLOR_MAGENTA,
    COLOR_CYAN,
    COLOR_WHITE,
    COLOR_DARKGRAY,
    COLOR_LIGHTGRAY
} ScreenColor;

void screenSetColor(ScreenColor fg, ScreenColor bg)
{
    const char *colors[] = {
        BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE, DARKGRAY, LIGHTGRAY};
    printf("%s%s", colors[fg], colors[bg - COLOR_BLACK + 40]);
}

void screenGotoxy(int x, int y)
{
    printf(ESC "[%d;%dH", y, x);
}

void screenInit(int useGraphics)
{
    printf(CLEARSCREEN);
    printf(HOMECURSOR);
    if (useGraphics)
    {
        printf(HIDECURSOR);
    }
}

void screenDestroy()
{
    printf(SHOWCURSOR);
    printf(RESET);
}

void screenSetTextStyle(const char *style)
{
    printf("%s", style);
}

void screenClear()
{
    printf(CLEARSCREEN);
    printf(HOMECURSOR);
}

void screenUpdate()
{
    fflush(stdout);
}

#endif
