#include "LuxComponent.h"

class_default_implementations(Component, (virtual_table_type(Component) *vtable, byte type), (vtable, type),
    (
        this->vtable = vtable;
        this->type = type;
    ),
    (
        NONE
    )
)
