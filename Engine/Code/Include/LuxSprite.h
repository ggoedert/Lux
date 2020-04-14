#ifndef LUX_SPRITE_H
#define LUX_SPRITE_H

#include "LuxAsset.h"

#define typeof_Texture2D 0x6a // String_GetHashCode8("Texture2D")
#define typeof_Sprite    0x79 // String_GetHashCode8("Sprite")

derived_class (Sprite, Asset,
    byte width, height;
    byte *data;
);
class_default_prototypes(Sprite, word id, byte *texture2D);

#endif
