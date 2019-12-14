#include <stdlib.h>

#include "Scene.h"
#include "GameObject.h"

#include "LuxGameObject.h"
#include "LuxCustomBehaviour.h"
//#include "LuxComponent.h"

#include "LuxDebug.h"

void GameObject_Constructor(GameObject *this, word id) {
    Object_Constructor(&this->Object, id);
    Stack_Constructor(&this->componentPtrs, sizeof(Component *));
Debug_Log("GameObject_Constructor $%04x", this);
    Scene_RegisterGameObject(this);
}

void GameObject_Destructor(GameObject *this) {
    int i;
    Component *component;
Debug_Log("GameObject_Destructor $%04x %d", this, this->componentPtrs.count);
    for (i=0; i<this->componentPtrs.count; i++) {
        component = *(Component **)Stack_Get(&this->componentPtrs, i);
        component->vtable->Delete(component);
    }
}

GameObject *GameObject_New(word id) {
    GameObject *this = (GameObject *)malloc(sizeof(GameObject));
Debug_Log("GameObject_New $%04x", this);
    if (this)
        GameObject_Constructor(this, id);
    return this;
}

void GameObject_Delete(GameObject *this) {
Debug_Log("GameObject_Delete $%04x", this);
    GameObject_Destructor(this);
    free(this);
}

void GameObject_Run(GameObject *this) {
    int i;
    CustomBehaviour *customBehaviour;

Debug_Log("GameObject_Run $%04x", this);
    for (i=0; i<this->componentPtrs.count; i++) {
        customBehaviour = *(CustomBehaviour **)Stack_Get(&this->componentPtrs, i);
        customBehaviour->vtable->Update(customBehaviour);
    }
}
