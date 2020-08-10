#ifndef LUX_LIST_H
#define LUX_LIST_H

#include "LuxTypes.h"

#define List Collection
    #define List_Constructor Collection_Constructor
    #define List_Destructor Collection_Destructor
    #define List_New Collection_New
    #define List_Delete Collection_Delete
#define List_SetCapacity Collection_SetCapacity
#define List_VoidAdd(...) Collection_VoidAdd(__VA_ARGS__)
#define List_Add(...) Collection_Add(__VA_ARGS__)
void List_VoidRemove(List *this, void *item);
#define List_Remove(this, item) List_VoidRemove(this, &item)
void List_RemoveAt(List *this, ColUInt index);
void *List_VoidItem(List *this, ColUInt index);
#define List_Item(this, Type, index) (*(Type *)List_VoidItem(this, index))
#define List_Clear(...) Collection_Clear(__VA_ARGS__)

#endif
