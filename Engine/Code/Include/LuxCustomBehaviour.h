#ifndef LUX_CUSTOM_BEHAVIOUR_H
#define LUX_CUSTOM_BEHAVIOUR_H

#include "LuxBehaviour.h"

#define CUSTOMBEHAVIOUR_TYPE 0x0426//String_GetHashCode("CustomBehaviour")

derived_virtual_class (CustomBehaviour, Behaviour,
    (
        NONE
    ),
    (
        void (*Start)(CustomBehaviour *this);
        void (*Update)(CustomBehaviour *this);
    )
);
typedef void (*CustomBehaviour_Start_Type)(CustomBehaviour *this);
typedef void (*CustomBehaviour_Update_Type)(CustomBehaviour *this);
class_constructor_destructor_prototypes(CustomBehaviour, virtual_table(Component) *component_vtable, virtual_table(CustomBehaviour) *customBehaviour_vtable);

#endif
