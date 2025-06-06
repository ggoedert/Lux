#ifndef LUX_STACK_H
#define LUX_STACK_H

#include "LuxTypes.h"

#define Stack Collection
    #define Stack_Constructor Collection_Constructor
    #define Stack_Destructor Collection_Destructor
    #define Stack_New Collection_New
    #define Stack_Delete Collection_Delete
#define Stack_SetCapacity Collection_SetCapacity
#define Stack_Push(this, Type, item) Collection_Add(this, Type, item)
void *Stack_VoidPop(Stack *this);
#define Stack_Pop(this, Type) (*(Type *)Stack_VoidPop(this))
void *Stack_VoidPeek(List *this);
#define Stack_Peek(this, Type) (*(Type *)Stack_VoidPeek(this))
#define Stack_Clear(this) Collection_Clear(this)

#endif
