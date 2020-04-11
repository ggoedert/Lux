#include "LuxStorage.h"

class_default_implementations(Storage, (virtual_table_type(Storage) *vtable), (vtable),
    (
        this->vtable = vtable;
    ),
    (
        NONE
    )
)
