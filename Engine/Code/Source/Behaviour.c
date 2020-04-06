#include "LuxBehaviour.h"

class_default_implementations(Behaviour, (virtual_table_type(Component) *vtable, byte type), (vtable, type),
    (
        Component_Constructor(&this->Component, vtable, type);
    ),
    (
        Component_Destructor(&this->Component);
    )
)
