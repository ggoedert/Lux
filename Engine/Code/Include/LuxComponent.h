#ifndef LUX_COMPONENT_H
#define LUX_COMPONENT_H

#include <stdbool.h>

#include "LuxTypes.h"

#define CUSTOM_BEHAVIOUR 0x1
#define RENDERER         0x2

virtual_class (Component,
    (
        byte type;
    ),
    (
        void (*Delete)(Component *this);
    )
);
typedef void (*Component_Delete_Type)(Component *this);
class_default_prototypes(Component, virtual_table_type(Component) *vtable, byte type);

#endif
