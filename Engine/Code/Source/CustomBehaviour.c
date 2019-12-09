#include "LuxCustomBehaviour.h"

void CustomBehaviour_Constructor(CustomBehaviour *this, virtual_table(CustomBehaviour) *vtable, char *name) {
    Behaviour_Constructor(&this->Behaviour, name);
    this->vtable = vtable;
}
