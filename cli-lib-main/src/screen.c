#include "screen.h"

#define BOX_HLINE '-'
#define BOX_VLINE '|'
#define BOX_UPLEFT '+'
#define BOX_UPRIGHT '+'
#define BOX_DWNLEFT '+'
#define BOX_DWNRIGHT '+'

#define MINX 0
#define MINY 0
#define MAXX 80 // Width of the console window
#define MAXY 25 // Height of the console window

typedef enum
{
    ENUM_BLACK,
    ENUM_RED,
    ENUM_GREEN,
    ENUM_YELLOW,
    ENUM_BLUE,
    ENUM_MAGENTA,
    ENUM_CYAN,
    ENUM_WHITE,
    ENUM_LIGHTGRAY,
    ENUM_LIGHTRED,
    ENUM_LIGHTGREEN,
    ENUM_LIGHTYELLOW,
    ENUM_LIGHTBLUE,
    ENUM_LIGHTMAGENTA,
    ENUM_LIGHTCYAN,
    ENUM_LIGHTWHITE
} screenColor;

void screenDrawBorders()
{
    char hbc = BOX_HLINE;
    char vbc = BOX_VLINE;

    screenClear();
    screenBoxEnable();

    screenGotoxy(MINX, MINY);
    printf("%c", BOX_UPLEFT);

    for (int i = MINX + 1; i < MAXX; i++)
    {
        screenGotoxy(i, MINY);
        printf("%c", hbc);
    }
    screenGotoxy(MAXX, MINY);
    printf("%c", BOX_UPRIGHT);

    for (int i = MINY + 1; i < MAXY; i++)
    {
        screenGotoxy(MINX, i);
        printf("%c", vbc);
        screenGotoxy(MAXX, i);
        printf("%c", vbc);
    }

    screenGotoxy(MINX, MAXY);
    printf("%c", BOX_DWNLEFT);
    for (int i = MINX + 1; i < MAXX; i++)
    {
        screenGotoxy(i, MAXY);
        printf("%c", hbc);
    }
    screenGotoxy(MAXX, MAXY);
    printf("%c", BOX_DWNRIGHT);

    screenBoxDisable();
}

void screenInit(int drawBorders)
{
    screenClear();
    if (drawBorders)
        screenDrawBorders();
    screenHomeCursor();
    screenHideCursor();
}

void screenDestroy()
{
    printf("%s[0;39;49m", ESC); // Reset colors
    screenSetNormal();
    screenClear();
    screenHomeCursor();
    screenShowCursor();
}

void screenGotoxy(int x, int y)
{
    x = (x < 0 ? 0 : (x >= MAXX ? MAXX - 1 : x));
    y = (y < 0 ? 0 : (y >= MAXY ? MAXY - 1 : y));
    printf("%s[%d;%dH", ESC, y + 1, x + 1);
}

void screenSetColor(screenColor fg, screenColor bg)
{
    printf("%s[%d;%dm", ESC, fg + 30, bg + 40 + (fg > ENUM_LIGHTGRAY ? 60 : 0));
}
