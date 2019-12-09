#ifndef LUX_GAME_OBJECT_H
#define LUX_GAME_OBJECT_H

#include "LuxObject.h"
#include "LuxStack.h"

derived_class (GameObject, Object,
    Stack componentPtrs;
);
void GameObject_Constructor(GameObject *this, char *name);
void GameObject_Destructor(GameObject *this);
GameObject *GameObject_New(char *name);
void GameObject_Delete(GameObject *this);

#endif
