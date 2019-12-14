#include "LuxComponent.h"

void Component_Constructor(Component *this, virtual_table(Component) *vtable) {
    Object_Constructor(&this->Object, 0);
    this->vtable = vtable;
}

void Component_Destructor(Component *this) {
    Object_Destructor(&this->Object);
}

Component *Component_New() {
    return nullptr;
}

void Component_Delete(Component *this) {
}
