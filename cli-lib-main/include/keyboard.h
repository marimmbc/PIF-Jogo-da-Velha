#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <stdbool.h>

void keyboardInit();

void keyboardDestroy();

int keyhit();

int readch();

void enableSpecialKeys();

void disableSpecialKeys();

#endif