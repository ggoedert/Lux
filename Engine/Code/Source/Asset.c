#include "LuxAsset.h"

class_default_implementations(Asset, (byte type, word id, virtual_table_type(Object) *vtable), (type, id, vtable),
    (
        Object_Constructor(&this->Object, type, vtable);
        this->id = id;
    ),
    (
        Object_Destructor(&this->Object);
    )
)
