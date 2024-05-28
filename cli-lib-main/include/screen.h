#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <stdio.h>

// Terminal control sequences
#define ESC            "\033"
#define NORMALTEXT     "[0m"
#define BOLDTEXT       "[1m"
#define ITALICTEXT     "[3m"
#define BLINKTEXT      "[5m"
#define REVERSETEXT    "[7m"
#define HOMECURSOR     "[f"
#define SHOWCURSOR     "[?25h"
#define HIDECURSOR     "[?25l"
#define CLEARSCREEN    "[2J"

// BOX Drawing - Unix like terminals
#define BOX_ENABLE     "(0"
#define BOX_DISABLE    "(B"
#define BOX_VLINE      0x78
#define BOX_HLINE      0x71
#define BOX_UPLEFT     0x6C
#define BOX_UPRIGHT    0x6B
#define BOX_DWNLEFT    0x6D
#define BOX_DWNRIGHT   0x6A
#define BOX_CROSS      0x6E
#define BOX_TLEFT      0X74
#define BOX_TRIGHT     0X75
#define BOX_TUP        0X77
#define BOX_TDOWN      0X76

#define BOX_DIAMOND    0x60
#define BOX_BLOCK      0x61
#define BOX_DOT        0x7E

// screen constants
#define SCRSTARTX      3      // Initial and final screen positions for the game
#define SCRENDX        75     // It means the area that can be drawn 
#define SCRSTARTY      1
#define SCRENDY        23

#define MINX           1      // min screen horizontal pos
#define MINY           1      // min screen vertical pos
#define MAXX           80     // max screen horizontal pos
#define MAXY           24     // max screen vertical pos

#define BOARD_WIDTH    13     // Board width for the game
#define BOARD_HEIGHT   7      // Board height for the game

typedef enum {BLACK, RED, GREEN, BROWN, BLUE, MAGENTA, CYAN, LIGHTGRAY,
        DARKGRAY, LIGHTRED, LIGHTGREEN, YELLOW, LIGHTBLUE, 
        LIGHTMAGENTA, LIGHTCYAN, WHITE} screenColor; 

static inline void screenHomeCursor() {
    printf("%s%s", ESC, HOMECURSOR);
}

static inline void screenShowCursor() {
    printf("%s%s", ESC, SHOWCURSOR);
}

static inline void screenHideCursor() {
    printf("%s%s", ESC, HIDECURSOR);
}

static inline void screenClear() {
    screenHomeCursor();
    printf("%s%s", ESC, CLEARSCREEN);
}

static inline void screenUpdate() {
    fflush(stdout);
}

static inline void screenSetNormal() {
    printf("%s%s", ESC, NORMALTEXT);
}

static inline void screenSetBold() {
    printf("%s%s", ESC, BOLDTEXT);
}

static inline void screenSetBlink() {
    printf("%s%s", ESC, BLINKTEXT);
}

static inline void screenSetReverse() {
    printf("%s%s", ESC, REVERSETEXT);
}

static inline void screenBoxEnable() {
    printf("%s%s", ESC, BOX_ENABLE);
}

static inline void screenBoxDisable() {
    printf("%s%s", ESC, BOX_DISABLE);
}

void screenInit(int drawBorders);
void screenDestroy();
void screenGotoxy(int x, int y);
void screenSetColor(screenColor fg, screenColor bg);

void drawPiece(char piece, int row, int col);
void drawPieceTemp(char piece, int row, int col);

#endif /* __SCREEN_H__ */
