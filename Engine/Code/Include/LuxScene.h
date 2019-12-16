#ifndef LUX_SCENE_H
#define LUX_SCENE_H

#include "LuxDefs.h"

typedef void (*Scene_Load)(void);

LUX_DECLARE(Scene_Load, Scene_Loader, nullptr);

#endif
