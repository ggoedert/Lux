#include "LuxObject.h"

class_default_implementations(Object, (virtual_table_type(Object) *vtable), (vtable),
    (
        this->vtable = vtable;
    ),
    (
        NONE
    )
)
