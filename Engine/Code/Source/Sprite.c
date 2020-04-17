#include <string.h>

#include "LuxSprite.h"

#include "LuxDebug.h"
virtual_table_type(Object) virtual_table_instance(Sprite_Object) = {
    (Object_Delete_Type)Sprite_Delete
};
class_default_implementations(Sprite, (word id, byte *texture2D), (id, texture2D),
    (
        int size;
        Asset_Constructor(&this->Asset, typeof_Sprite, id, &virtual_table_instance(Sprite_Object));
        Debug_Log("Create Sprite");
        this->width = *texture2D++;
        this->height = *texture2D++;
        this->data = texture2D;
        size = this->width*this->height;
        this->data = malloc(size);
        memcpy(this->data, texture2D, size);
    ),
    (
        free(this->data);
        Debug_Log("Destroy Sprite");
        Asset_Destructor(&this->Asset);
    )
)
