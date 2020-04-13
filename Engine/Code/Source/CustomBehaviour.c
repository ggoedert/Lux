#include "LuxCustomBehaviour.h"

class_constructor_destructor_implementations(CustomBehaviour, (virtual_table_type(Object) *object_vtable, virtual_table_type(CustomBehaviour) *customBehaviour_vtable),
    (
        CustomBehaviour_Start_Type CustomBehaviour_Start;
        Behaviour_Constructor(&this->Behaviour, typeof_CustomBehaviour, object_vtable);
        this->vtable = customBehaviour_vtable;
        CustomBehaviour_Start = this->vtable->Start;
        if (CustomBehaviour_Start)
            CustomBehaviour_Start(this);
    ),
    (
        Behaviour_Destructor(&this->Behaviour);
    )
)
