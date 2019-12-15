#include "LuxCollections.h"

void *List_Item(List *this, int index) {
    return (((byte *)this->items)+(this->sizeOfItem*index));
}
