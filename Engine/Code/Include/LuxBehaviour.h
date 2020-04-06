#ifndef LUX_BEHAVIOUR_H
#define LUX_BEHAVIOUR_H

#include "LuxComponent.h"

derived_class (Behaviour, Component,
    NONE
);
class_default_prototypes(Behaviour, virtual_table_type(Component) *vtable, byte type);

#endif
