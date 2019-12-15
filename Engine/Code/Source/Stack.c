#include "LuxCollections.h"

void *Stack_Pop(Stack *this) {
    return (((byte *)this->items)+(this->sizeOfItem*(--this->count)));
}

void *Stack_Peek(List *this) {
    return (((byte *)this->items)+(this->sizeOfItem*this->count));
}
