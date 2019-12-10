#ifndef LUX_CUSTOM_BEHAVIOUR_H
#define LUX_CUSTOM_BEHAVIOUR_H

#include "LuxBehaviour.h"

derived_virtual_class (CustomBehaviour, Behaviour, (
    ), (
		void (*Start)(CustomBehaviour *this);
		void (*Update)(CustomBehaviour *this);
    )
);
void CustomBehaviour_Constructor(CustomBehaviour *this, virtual_table(CustomBehaviour) *vtable, word id);
#define CustomBehaviour_Destructor Behaviour_Destructor
//??CustomBehaviour *CustomBehaviour_New();
//??void CustomBehaviour_Delete(CustomBehaviour *this);
typedef void (*CustomBehaviour_Start)(CustomBehaviour *this);
typedef void (*CustomBehaviour_Update)(CustomBehaviour *this);

#endif
