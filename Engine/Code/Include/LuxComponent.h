#ifndef LUX_COMPONENT_H
#define LUX_COMPONENT_H

#include <stdbool.h>

#include "LuxDefs.h"

virtual_class (Component,
    (
        bool customBehaviour;
    ),
    (
        void (*Delete)(Component *this);
    )
);
typedef void (*Component_Delete_Type)(Component *this);
class_default_prototypes(Component, virtual_table(Component) *vtable);

#endif
