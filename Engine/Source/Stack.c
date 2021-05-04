#include "LuxCollections.h"

void *Stack_VoidPop(Stack *this) {
    return (((byte *)this->items)+(this->sizeOfItem*(--this->count)));
}

void *Stack_VoidPeek(List *this) {
    return (((byte *)this->items)+(this->sizeOfItem*this->count));
}
