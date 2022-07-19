#ifndef LUX_QUEUE_H
#define LUX_QUEUE_H

#include "LuxCollections.h"

#define Queue Collection
    #define Queue_Constructor Collection_Constructor
    #define Queue_Destructor Collection_Destructor
    #define Queue_New Collection_New
    #define Queue_Delete Collection_Delete
#define Queue_SetCapacity Collection_SetCapacity
#define Queue_Enqueue(this, Type, item) Collection_Add(this, Type, item)
#define Queue_Peek(this, Type) (*(Type *)List_VoidItem(this, 0))
#define Queue_Dequeue(this) List_RemoveAt(this, 0)
#define Queue_Clear(this) Collection_Clear(this)

#endif
