#ifndef LUX_SPRITE_H
#define LUX_SPRITE_H

#include "LuxAsset.h"

#define typeof_Sprite 0x79 // String_GetHashCode8("Sprite")

derived_class (Sprite, Asset,
    byte width, height;
    byte *data;
);
class_default_prototypes(Sprite, byte *texture2D);

#endif
