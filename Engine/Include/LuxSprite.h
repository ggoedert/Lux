#ifndef LUX_SPRITE_H
#define LUX_SPRITE_H

#include "LuxTypes.h"

#define typeof_Sprite    0x79 // String_GetHashCode8("Sprite")

class (Sprite,
    byte width, height;
    byte *data;
);
class_default_prototypes(Sprite, byte *texture2D);

#endif
