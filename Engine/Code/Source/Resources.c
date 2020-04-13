#include "LuxResources.h"
#include "LuxSprite.h"

List storageList;
//Storage *lastAccessedStorage = nullptr;

Asset *Resources_Create(byte *resource);

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

Asset *Resources_Reference(word id) {
    int i, j;
    Storage *currentStorage;
    byte *resource;
    Asset *ptr;

    /*if (hashmapcache has id) {
        hashmapcache[id].count++;
        return hashmapcache[id].ptr;
    }*/

    for (i=0; i<storageList.count; i++) {
        currentStorage = List_Item(&storageList, Storage *, i);
        resource = currentStorage->vtable->Load(id);
        if (nullptr != resource) {
            if (i) {
                for (j=i; j; j--)
                    List_Item(&storageList, Storage *, j) = List_Item(&storageList, Storage *, j-1);
                List_Item(&storageList, Storage *, 0) = currentStorage;
            }

            ptr = Resources_Create(resource);
            /*if (!(hashmapcache has id)) {
                create id at hashmapcache;
                hashmapcache[id].count = 0;
            }
            hashmapcache[id].ptr = ptr;
            hashmapcache[id].count++;*/

            return ptr;
        }
    }
    return nullptr;
}

void Resources_Unreference(word id) {
    /*if (hashmapcache has id) {
        hashmapcache[id].count--;
        if (0 == hashmapcache[id].count)
            hashmapcache[id].ptr->Delete();
    }*/
}

Asset *Resources_Create(byte *resource) {
    Asset *asset = nullptr;
    byte resourceType = *resource++;
    switch(resourceType) {
        case Texture2D:
            asset = (Asset *)Sprite_New(resource);
            Debug_Log("Resources_Create Texture2D %d %d", ((Sprite *)asset)->width, ((Sprite *)asset)->height);
            break;
    }
    return asset;
}

void Resources_Optimize() {
    int i;
    for (i=0; i<storageList.count; i++)
        List_Item(&storageList, Storage *, i)->vtable->Optimize();
}
