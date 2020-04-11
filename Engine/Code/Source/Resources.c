#include "LuxResources.h"

List storageList;

#include "LuxDebug.h"
void Resources_Init() {
    Debug_Log("Resources_Init");
    List_Constructor(&storageList, sizeof(Storage *));
}

#ifdef _DEBUG
void Resources_Finalize() {
    Debug_Log("Resources_Finalize");
    List_Destructor(&storageList);
}
#endif

void Resources_AddStorage(Storage *storage) {
    Debug_Log("Resources_AddStorage");
    List_Add(&storageList, Storage *, storage);
}

void *Resources_Load(word id) {
    return nullptr;
}

void Resources_Optimize() {
}
