#ifndef LUX_BEHAVIOUR_H
#define LUX_BEHAVIOUR_H

#include "LuxComponent.h"

derived_class(Behaviour, Component,
    EMPTY
);
component_default_prototypes(Behaviour, byte type, virtual_table_type(Component) *vtable);

#endif
