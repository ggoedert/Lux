#ifndef LUX_CUSTOM_BEHAVIOUR_H
#define LUX_CUSTOM_BEHAVIOUR_H

#include "LuxBehaviour.h"

derived_virtual_class (CustomBehaviour, Behaviour, (
        NONE
    ), (
        void (*Start)(CustomBehaviour *this);
        void (*Update)(CustomBehaviour *this);
    )
);
typedef void (*CustomBehaviour_Start_Type)(CustomBehaviour *this);
typedef void (*CustomBehaviour_Update_Type)(CustomBehaviour *this);
void CustomBehaviour_Constructor(CustomBehaviour *this, virtual_table(Component) *component_vtable, virtual_table(CustomBehaviour) *customBehaviour_vtable);
#define CustomBehaviour_Destructor Behaviour_Destructor

#endif
