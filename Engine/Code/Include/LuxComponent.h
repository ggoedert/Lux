#ifndef LUX_COMPONENT_H
#define LUX_COMPONENT_H

#include "LuxTypes.h"

virtual_class (Component,
    (
        byte type;
    ),
    (
        void (*Delete)(Component *this);
    )
);
typedef void (*Component_Delete_Type)(Component *this);
class_default_prototypes(Component, byte type, virtual_table_type(Component) *vtable);

#endif
