#include <string.h>

#include "LuxCollections.h"

void List_VoidRemove(List *this, void *item) {
    ColUInt index;
    for (index=0; index<this->count; index++) {
        if (memcmp(((byte *)this->items)+(this->sizeOfItem*index), item, this->sizeOfItem) == 0) {
            List_RemoveAt(this, index);
            return;
        }
    }
}

void List_RemoveAt(List *this, ColUInt index) {
    int moveItems;
    --this->count;
    moveItems = ((int)this->count)-((int)index);
    if (moveItems > 0)
        memmove(((byte *)this->items)+(this->sizeOfItem*index), ((byte *)this->items)+(this->sizeOfItem*(index+1)), this->sizeOfItem*moveItems);
}

void *List_VoidItem(List *this, ColUInt index) {
    return (((byte *)this->items)+(this->sizeOfItem*index));
}
