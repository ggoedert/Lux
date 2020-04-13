#include "LuxAsset.h"

class_default_implementations(Asset, (byte type, virtual_table_type(Object) *vtable), (type, vtable),
    (
        Object_Constructor(&this->Object, vtable);
        this->type = type;
    ),
    (
        Object_Destructor(&this->Object);
    )
)
