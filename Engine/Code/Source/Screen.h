#ifndef SCREEN_H
#define SCREEN_H

#include "LuxTypes.h"

void Screen_Init(void);
void Screen_WaitVBlank(void);
void Screen_DrawSprite(byte *data, byte width, byte height, byte x, byte y);

#endif
