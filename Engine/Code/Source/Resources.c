#include "LuxResources.h"

List storageList;
Storage *lastAccessedStorage = nullptr;

void *Resources_Create(byte *resource);

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
    int i;
    Storage *currentStorage;
    byte *resource;

    if (nullptr != lastAccessedStorage) {
        resource = lastAccessedStorage->vtable->Load(id);
        if (nullptr != resource)
            return Resources_Create(resource);
    }
    for (i=0; i<storageList.count; i++) {
        currentStorage = List_Item(&storageList, Storage *, i);
        if (currentStorage != lastAccessedStorage) {
            resource = currentStorage->vtable->Load(id);
            if (nullptr != resource) {
                lastAccessedStorage = currentStorage;
                return Resources_Create(resource);
            }
        }
    }
    return nullptr;
}

void *Resources_Create(byte *resource) {
    word resourceType = *(word *)resource;
    resource += 2;
    switch(resourceType) {
        case Texture2D:
            Debug_Log("Resources_Create Texture2D");
            return nullptr;
    }
    return nullptr;
}

void Resources_Optimize() {
    int i;
    for (i=0; i<storageList.count; i++)
        List_Item(&storageList, Storage *, i)->vtable->Optimize();
}
