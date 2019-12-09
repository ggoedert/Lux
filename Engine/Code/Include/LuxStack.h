#ifndef LUX_STACK_H
#define LUX_STACK_H

#include "LuxDefs.h"

class (Stack,
    byte sizeOfItem;
    byte count;
    byte capacity;
    void *items;
);
void Stack_Constructor(Stack *this, byte sizeOfItem);
#define Stack_Destructor(this) free((this)->items)
Stack *Stack_New(byte sizeOfItem);
void Stack_Delete(Stack *this);
void *Stack_Push(Stack *this);
void *Stack_Get(Stack *this, int index);
void *Stack_Pop(Stack *this);
#define Stack_Clear(this) (this)->count=0

#endif
