#include "LuxComponent.h"

class_default_implementations(Component, (byte type, virtual_table_type(Object) *vtable), (type, vtable),
    (
        Object_Constructor(&this->Object, type, vtable);
    ),
    (
        Object_Destructor(&this->Object);
    )
)
