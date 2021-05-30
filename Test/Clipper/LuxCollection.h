#ifndef LUX_COLLECTION_H
#define LUX_COLLECTION_H

#include "LuxTypes.h"

class (Collection,
    byte sizeOfItem;
    ColUInt count;
    ColUInt capacity;
    void *items;
);
class_default_prototypes(Collection, byte sizeOfItem);
void Collection_SetCapacity(Collection *this, ColUInt capacity);
void *Collection_VoidAdd(Collection *this);
#define Collection_Add(this, Type, item) *(Type *)Collection_VoidAdd(this) = item
#define Collection_Clear(this) (this)->count=0

#endif
