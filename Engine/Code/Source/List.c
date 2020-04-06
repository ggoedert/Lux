#include <string.h>

#include "LuxCollections.h"

void List_RemoveAt(List *this, int index) {
    int moveItems;
    --this->count;
    moveItems = this->count-index;
    if (moveItems > 0)
        memmove(((byte *)this->items)+(this->sizeOfItem*index), ((byte *)this->items)+(this->sizeOfItem*(index+1)), this->sizeOfItem*moveItems);
}

void *List_VoidItem(List *this, int index) {
    return (((byte *)this->items)+(this->sizeOfItem*index));
}
