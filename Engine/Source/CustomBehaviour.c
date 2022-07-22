#include "LuxCustomBehaviour.h"

void CustomBehaviour_Constructor(GameObject *gameObject, CustomBehaviour *this, virtual_table_type(Component) *component_vtable, virtual_table_type(CustomBehaviour) *customBehaviour_vtable) {
    CustomBehaviour_Start_Type CustomBehaviour_Start;
    Behaviour_Constructor(gameObject, &this->Behaviour, typeof_CustomBehaviour, component_vtable);
    this->vtable = customBehaviour_vtable;
    CustomBehaviour_Start = this->vtable->Start;
    if (CustomBehaviour_Start)
        CustomBehaviour_Start(gameObject, this);
}

void CustomBehaviour_Destructor(GameObject *gameObject, CustomBehaviour *this) {
    CustomBehaviour_OnDestroy_Type CustomBehaviour_OnDestroy = this->vtable->OnDestroy;
    if (CustomBehaviour_OnDestroy)
        CustomBehaviour_OnDestroy(gameObject, this);
    Behaviour_Destructor(gameObject, &this->Behaviour);
}
