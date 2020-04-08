#ifndef LUX_COLLECTION_H
#define LUX_COLLECTION_H

#include "LuxTypes.h"

class (Collection,
    byte sizeOfItem;
    byte count;
    byte capacity;
    void *items;
);
class_default_prototypes(Collection, byte sizeOfItem);
void Collection_SetCapacity(Collection *this, byte capacity);
void *Collection_VoidAdd(Collection *this);
#define Collection_Add(C, T, I) do { *(T **)Collection_VoidAdd(C) = I; } while(false)
#define Collection_Clear(this) (this)->count=0

#endif
