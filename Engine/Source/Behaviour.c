#include "LuxBehaviour.h"

class_default_implementations(Behaviour, (byte type, virtual_table_type(Object) *vtable), (type, vtable),
    (
        Component_Constructor(&this->Component, type, vtable);
    ),
    (
        Component_Destructor(&this->Component);
    )
)
