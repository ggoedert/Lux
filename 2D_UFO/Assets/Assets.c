#include "LuxEngine.h"
#include "LuxSceneManagement.h"

#include "Assets.h"
#include "ResourceUFO.h"

Assets assets;

virtual_table_type(Storage) virtual_table_instance(Assets_Storage) = {
    (Storage_Load_Type)Assets_Load,
    (Storage_Optimize_Type)nullptr
};
derived_class_simple_default_implementations(Assets, Storage, (&virtual_table_instance(Assets_Storage)))

byte *Assets_Load(word id) {
    if (UFO == id)
        return ResourceUFO;
    return nullptr;
}
