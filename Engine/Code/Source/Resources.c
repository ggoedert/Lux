#include "LuxResources.h"
#include "LuxSprite.h"

class (AssetReference,
    word id;
    Asset *asset;
    byte count;
);
class_default_implementations(AssetReference, (word id, Asset *asset), (id, asset),
    (
        this->id = id;
        this->asset = asset;
        this->count = 1;
    ),
    (
        EMPTY
    )
)
List assetReferenceList;
List storageList;

Asset *Resources_Create(word id, byte *resource);
ColUInt Resources_FindAssetReferenceIndex(word id);

#include "LuxDebug.h"
void Resources_Init() {
    Debug_Log("Resources_Init");
    List_Constructor(&assetReferenceList, sizeof(AssetReference));
    List_Constructor(&storageList, sizeof(Storage *));
}

#ifdef _DEBUG
void Resources_Finalize() {
    Debug_Log("Resources_Finalize");
    List_Destructor(&storageList);
    List_Destructor(&assetReferenceList);
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
    AssetReference *assetReference;
    byte assetReferenceListIndex;

    Debug_Log("Resources_Reference $%04x", id);
    assetReferenceListIndex = Resources_FindAssetReferenceIndex(id);
    if (assetReferenceListIndex != ColUIntMax) {
        assetReference = &List_Item(&assetReferenceList, AssetReference, assetReferenceListIndex);
        ++assetReference->count;
        return assetReference->asset;
    }

    for (i=0; i<storageList.count; ++i) {
        currentStorage = List_Item(&storageList, Storage *, i);
        resource = currentStorage->vtable->Load(id);
        if (nullptr != resource) {
            if (i) {
                for (j=i; j; --j)
                    List_Item(&storageList, Storage *, j) = List_Item(&storageList, Storage *, j-1);
                List_Item(&storageList, Storage *, 0) = currentStorage;
            }
            assetReference = List_VoidAdd(&assetReferenceList);
            AssetReference_Constructor(assetReference, id, Resources_Create(id, resource));
            return assetReference->asset;
        }
    }

    return nullptr;
}

void Resources_Unreference(word id) {
    AssetReference *assetReference;
    byte assetReferenceListIndex = Resources_FindAssetReferenceIndex(id);
    if (assetReferenceListIndex != ColUIntMax) {
        Debug_Log("Resources_Unreference $%04x", id);
        assetReference = &List_Item(&assetReferenceList, AssetReference, assetReferenceListIndex);
        --assetReference->count;
        if (0 == assetReference->count) {
            Object *object = &assetReference->asset->Object;
            object->vtable->Delete(object);
            List_RemoveAt(&assetReferenceList, assetReferenceListIndex);
        }
    }
}

Asset *Resources_Create(word id, byte *resource) {
    Asset *asset = nullptr;
    byte resourceType = *resource++;
    switch(resourceType) {
        case typeof_Texture2D:
            asset = (Asset *)Sprite_New(id, resource);
            Debug_Log("Resources_Create Texture2D %d %d", ((Sprite *)asset)->width, ((Sprite *)asset)->height);
            break;
    }
    return asset;
}

void Resources_Optimize() {
    int i;
    Storage_Optimize_Type optimize;
    for (i=0; i<storageList.count; ++i) {
        optimize = List_Item(&storageList, Storage *, i)->vtable->Optimize;
        if (nullptr != optimize)
            optimize();
    }
}

ColUInt Resources_FindAssetReferenceIndex(word id) {
    int i;
    AssetReference *assetReference;
    for (i=0; i<assetReferenceList.count; ++i) {
        assetReference = &List_Item(&assetReferenceList, AssetReference, i);
        if (assetReference->id == id)
            return i;
    }
    return ColUIntMax;
}
