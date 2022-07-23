#include "LuxBehaviour.h"

component_no_destructor_implementations(Behaviour, (byte type, virtual_table_type(Component) *vtable), (type, vtable),
    (
        Component_Constructor(gameObject, &this->Component, type, vtable);
    )
)
