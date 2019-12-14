#ifndef LUX_COMPONENT_H
#define LUX_COMPONENT_H

#include "LuxObject.h"

derived_virtual_class (Component, Object, (
        NONE
    ), (
        void (*Delete)(Component *this);
    )
);
typedef void (*Component_Delete_Type)(Component *this);
void Component_Constructor(Component *this, virtual_table(Component) *vtable);
void Component_Destructor(Component *this);
Component *Component_New();
void Component_Delete(Component *this);

#endif
