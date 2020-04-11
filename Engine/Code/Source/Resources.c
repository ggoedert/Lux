#include "LuxResources.h"

List storageList;

void Resources_Init() {
    List_Constructor(&storageList, sizeof(Storage *));
}

void Resources_AddStorage(Storage *storage) {
    List_Add(&storageList, Storage, storage);
}

void *Resources_Load(word id) {
    return nullptr;
}

void Resources_Optimize() {
}
