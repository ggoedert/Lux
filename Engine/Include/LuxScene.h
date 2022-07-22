#ifndef LUX_SCENE_H
#define LUX_SCENE_H

#include "LuxTypes.h"

typedef void (*Scene_Load)();
#ifndef __CC65__
void Scene_Finalize();
#endif

#endif
