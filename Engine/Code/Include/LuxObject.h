#ifndef LUX_OBJECT_H
#define LUX_OBJECT_H

#include "LuxDefs.h"

class (Object,
    word id;
);
void Object_Constructor(Object *this, word id);
void Object_Destructor(Object *this);
Object *Object_New(word id);
void Object_Delete(Object *this);

#endif
