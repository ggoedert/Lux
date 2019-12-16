#include "LuxComponent.h"

class_default_implementations(Component, (virtual_table(Component) *vtable), (vtable),
    (
        this->vtable = vtable;
        this->customBehaviour = false;
    ),
    (
        NONE
    )
)
