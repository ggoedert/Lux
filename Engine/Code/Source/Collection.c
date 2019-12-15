#include "LuxCollection.h"

class_default_implementations(Collection, (byte sizeOfItem), (sizeOfItem),
    (
        this->sizeOfItem = sizeOfItem;
        this->count = 0;
        this->capacity = 0;
        this->items = nullptr;
    ),
    (
        free(this->items);
    )
)

void Collection_SetCapacity(Collection *this, byte capacity) {
    if (capacity > this->capacity) {
        this->capacity = capacity;
        this->items = realloc(this->items, this->capacity*this->sizeOfItem);
    }
}

void *Collection_Add(Collection *this) {
    if (this->count == this->capacity) {
        int newCount = this->count+1;
        if (newCount<=2)
            this->capacity = newCount;
        else if (newCount==3)
            this->capacity = 4;
        else 
            this->capacity = newCount+(newCount>>3)+(newCount<9?3:6);
        this->items = realloc(this->items, this->capacity*this->sizeOfItem);
    }
    return (((byte *)this->items)+(this->sizeOfItem*(this->count++)));
}
