#include "LuxComponent.h"

component_constructor_implementation(Component, (byte type, virtual_table_type(Component)* vtable),
    Object_Constructor(&this->Object, type);
    this->vtable = vtable;
)
