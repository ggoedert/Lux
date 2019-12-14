#ifndef LUX_COMPONENT_H
#define LUX_COMPONENT_H

#include "LuxObject.h"

derived_virtual_class (Component, Object,
    (
        NONE
    ),
    (
        void (*Delete)(Component *this);
    )
);
typedef void (*Component_Delete_Type)(Component *this);
class_default_prototypes(Component, virtual_table(Component) *vtable);

#endif
