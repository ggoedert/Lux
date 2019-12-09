#ifndef LUX_OBJECT_H
#define LUX_OBJECT_H

#include "LuxDefs.h"

class (Object,
    char *name;
);
void Object_Constructor(Object *this, char *name);
void Object_Destructor(Object *this);
Object *Object_New(char *name);
void Object_Delete(Object *this);

#endif
