#ifndef LUX_GAME_OBJECT_H
#define LUX_GAME_OBJECT_H

#include "LuxObject.h"
#include "LuxStack.h"

derived_class (GameObject, Object,
    Stack componentPtrs;
);
void GameObject_Constructor(GameObject *this, word id);
void GameObject_Destructor(GameObject *this);
GameObject *GameObject_New(word id);
void GameObject_Delete(GameObject *this);

#endif
