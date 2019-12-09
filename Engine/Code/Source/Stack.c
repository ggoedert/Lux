#include <stdlib.h>
#include <string.h>

#include "LuxStack.h"

void Stack_Constructor(Stack *this, byte sizeOfItem) {
    this->sizeOfItem = sizeOfItem;
    this->count = 0;
    this->capacity = 0;
    this->items = nullptr;
}

Stack *Stack_New(byte sizeOfItem) {
    Stack *result = (Stack *)malloc(sizeof(Stack));
    Stack_Constructor(result, sizeOfItem);
    return result;
}

void Stack_Delete(Stack *this) {
    Stack_Destructor(this);
    free(this);
}

void *Stack_Push(Stack *this) {
    if (this->count == this->capacity) {
        int newCount = this->count+1;
        this->capacity = newCount+(newCount>>3)+(newCount<9?3:6);
        this->items = realloc(this->items, this->capacity*this->sizeOfItem);
    }
    return (((byte *)this->items)+(this->sizeOfItem*(this->count++)));
}

void *Stack_Get(Stack *this, int index) {
    return (((byte *)this->items)+(this->sizeOfItem*index));
}

void *Stack_Pop(Stack *this) {
    return (((byte *)this->items)+(this->sizeOfItem*(--this->count)));
}
