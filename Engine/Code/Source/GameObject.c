#include "LuxGameObject.h"
#include "LuxComponent.h"

void GameObject_Constructor(GameObject *this, char *name) {
    Object_Constructor(&this->Object, name);
    Stack_Constructor(&this->componentPtrs, sizeof(Component *));
}

void GameObject_Destructor(GameObject *this) {
}

GameObject *GameObject_New(char *name) {
    return nullptr;
}

void GameObject_Delete(GameObject *this) {
}
