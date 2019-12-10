#include "LuxCustomBehaviour.h"

void CustomBehaviour_Constructor(CustomBehaviour *this, virtual_table(CustomBehaviour) *vtable, word id) {
    Behaviour_Constructor(&this->Behaviour, id);
    this->vtable = vtable;
}
