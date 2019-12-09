#include "LuxObject.h"

void Object_Constructor(Object *this, char *name) {
    this->name = name;    
}

void Object_Destructor(Object *this) {
}

Object *Object_New(char *name) {
    return nullptr;
}

void Object_Delete(Object *this) {
}
