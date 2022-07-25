#ifndef SCREEN_H
#define SCREEN_H

#include "LuxTypes.h"
#include "LuxSprite.h"

void Screen_Init();
#ifndef __CC65__
void Scene_Finalize();
#endif
void Screen_WaitVBlank();
void Screen_DrawSprite(Sprite *sprite, byte mask, byte x, byte y);

#endif
