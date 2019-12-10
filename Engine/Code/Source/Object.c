#include "LuxObject.h"

void Object_Constructor(Object *this, word id) {
    this->id = id;
}

void Object_Destructor(Object *this) {
}

Object *Object_New(word id) {
    return nullptr;
}

void Object_Delete(Object *this) {
}
