#include "LuxComponent.h"

class_default_implementations(Component, (byte type, virtual_table_type(Component) *vtable), (type, vtable),
    (
        this->type = type;
        this->vtable = vtable;
    ),
    (
        NONE
    )
)
