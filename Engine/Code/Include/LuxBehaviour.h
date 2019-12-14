#ifndef LUX_BEHAVIOUR_H
#define LUX_BEHAVIOUR_H

#include "LuxComponent.h"

derived_class (Behaviour, Component,
    NONE
);
void Behaviour_Constructor(Behaviour *this, virtual_table(Component) *vtable);
void Behaviour_Destructor(Behaviour *this);
Behaviour *Behaviour_New(word id);
void Behaviour_Delete(Behaviour *this);

#endif
