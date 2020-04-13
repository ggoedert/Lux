#include "LuxSpriteRenderer.h"
#include "LuxResources.h"

virtual_table_type(Object) virtual_table_instance(Object_SpriteRenderer) = {
    (Object_Delete_Type)SpriteRenderer_Delete
};
virtual_table_type(Renderer) virtual_table_instance(Renderer_SpriteRenderer) = {
    (Renderer_Render_Type)SpriteRenderer_Render
};
class_default_implementations(SpriteRenderer, (Sprite *sprite), (sprite),
    (
        Renderer_Constructor(&this->Renderer, &virtual_table_instance(Object_SpriteRenderer), &virtual_table_instance(Renderer_SpriteRenderer));
        this->sprite = sprite;
    ),
    (
        Resources_Unreference(this->sprite->Asset.Object.type);
        Renderer_Destructor(&this->Renderer);
    )
)

#include "LuxDebug.h"
void SpriteRenderer_Render(SpriteRenderer *this) {
    //TODO!!!
    //Debug_Log("SpriteRenderer_Render");
}
