#ifndef LUX_GAME_OBJECT_H
#define LUX_GAME_OBJECT_H

#include "LuxObject.h"
#include "LuxStack.h"

derived_class (GameObject, Object,
    Stack componentPtrs;
);
class_new_delete_prototypes(GameObject, word id);

#endif
