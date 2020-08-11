#include "Screen.h"

#include "LuxSpriteRenderer.h"
#include "LuxResources.h"

virtual_table_type(Object) virtual_table_instance(SpriteRenderer_Object) = {
    (Object_Delete_Type)SpriteRenderer_Delete
};
virtual_table_type(Renderer) virtual_table_instance(SpriteRenderer_Renderer) = {
    (Renderer_Render_Type)SpriteRenderer_Render
};
class_default_implementations(SpriteRenderer, (Sprite *sprite), (sprite),
    (
        Renderer_Constructor(&this->Renderer, &virtual_table_instance(SpriteRenderer_Object), &virtual_table_instance(SpriteRenderer_Renderer));
        this->sprite = sprite;
    ),
    (
        Resources_Unreference(this->sprite->Asset.id);
        Renderer_Destructor(&this->Renderer);
    )
)

#include "LuxDebug.h"
void SpriteRenderer_Render(SpriteRenderer *this, Transform *transform) {
    //TODO!!!
    //Debug_Log("SpriteRenderer_Render");
    Screen_DrawSprite(this->sprite->data, this->sprite->width, this->sprite->height, transform->position.x, transform->position.y);
}
