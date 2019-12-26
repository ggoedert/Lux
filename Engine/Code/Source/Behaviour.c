#include "LuxBehaviour.h"

class_default_implementations(Behaviour, (virtual_table_type(Component) *vtable), (vtable),
    (
        Component_Constructor(&this->Component, vtable);
    ),
    (
        Component_Destructor(&this->Component);
    )
)
