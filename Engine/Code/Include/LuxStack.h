#ifndef LUX_STACK_H
#define LUX_STACK_H

#include "LuxTypes.h"

#define Stack Collection
    #define Stack_Constructor Collection_Constructor
    #define Stack_Destructor Collection_Destructor
    #define Stack_New Collection_New
    #define Stack_Delete Collection_Delete
#define Stack_SetCapacity Collection_SetCapacity
#define Stack_Push(...) Collection_Add(__VA_ARGS__)
void *Stack_VoidPop(Stack *this);
#define Stack_Pop(S, T) (*(T **)Stack_VoidPop(S))
void *Stack_VoidPeek(List *this);
#define Stack_Peek(S, T) (*(T **)Stack_VoidPeek(S))
#define Stack_Clear(...) Collection_Clear(__VA_ARGS__)

#endif
