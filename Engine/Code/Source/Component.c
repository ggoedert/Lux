#include "LuxComponent.h"

class_default_implementations(Component, (virtual_table(Component) *vtable), (vtable),
    (
        Object_Constructor(&this->Object, 0);
        this->vtable = vtable;
    ),
    (
        Object_Destructor(&this->Object);
    )
)
