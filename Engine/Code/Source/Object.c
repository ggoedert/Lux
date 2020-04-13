#include "LuxObject.h"

class_default_implementations(Object, (byte type, virtual_table_type(Object) *vtable), (type, vtable),
    (
        this->vtable = vtable;
        this->type = type;
    ),
    (
        NONE
    )
)
