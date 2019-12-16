#include "LuxCustomBehaviour.h"

class_constructor_destructor_implementations(CustomBehaviour, (virtual_table(Component) *component_vtable, virtual_table(CustomBehaviour) *customBehaviour_vtable),
    (
        Behaviour_Constructor(&this->Behaviour, component_vtable);
        ((Component *)this)->customBehaviour = true;
        this->vtable = customBehaviour_vtable;
        this->vtable->Start(this);
    ),
    (
        Behaviour_Destructor(&this->Behaviour);
    )
)
