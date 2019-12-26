#ifndef LUX_LIST_H
#define LUX_LIST_H

#include "LuxTypes.h"

#define List Collection
    #define List_Constructor Collection_Constructor
    #define List_Destructor Collection_Destructor
    #define List_New Collection_New
    #define List_Delete Collection_Delete
#define List_SetCapacity Collection_SetCapacity
#define List_Add Collection_Add
void List_RemoveAt(List *this, int index);
void *List_Item(List *this, int index);
#define List_Clear(...) Collection_Clear(__VA_ARGS__)

#endif
