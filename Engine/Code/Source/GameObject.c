#include "LuxGameObject.h"
#include "LuxComponent.h"

void GameObject_Constructor(GameObject *this, word id) {
    Object_Constructor(&this->Object, id);
    Stack_Constructor(&this->componentPtrs, sizeof(Component *));
}

void GameObject_Destructor(GameObject *this) {
}

GameObject *GameObject_New(word id) {
    return nullptr;
}

void GameObject_Delete(GameObject *this) {
}
