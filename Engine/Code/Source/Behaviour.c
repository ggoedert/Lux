#include "LuxBehaviour.h"

void Behaviour_Constructor(Behaviour *this, virtual_table(Component) *vtable) {
    Component_Constructor(&this->Component, vtable);
}

void Behaviour_Destructor(Behaviour *this) {
}

Behaviour *Behaviour_New(word id) {
    return nullptr;
}

void Behaviour_Delete(Behaviour *this) {
}
