#include "LuxComponent.h"

class_default_implementations(Component, (virtual_table_type(Component) *vtable), (vtable),
    (
        this->vtable = vtable;
        this->typeId = 0;
    ),
    (
        NONE
    )
)
