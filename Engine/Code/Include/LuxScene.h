#ifndef LUX_SCENE_H
#define LUX_SCENE_H

#include "LuxDefs.h"

LUX_DECLARE(word, Scene_id, 0xBF4C/*String_GetHashCode("Untitled")*/);
typedef void (*Scene_Load)(void);

#endif
