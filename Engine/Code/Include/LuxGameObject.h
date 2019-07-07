#ifndef LUX_GAME_OBJECT_H
#define LUX_GAME_OBJECT_H

#include "LuxObject.h"
#include "LuxScene.h"

derived_class (GameObject, Object,
    Scene *scene;
);

#endif
