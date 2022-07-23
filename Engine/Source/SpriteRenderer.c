#include "Screen.h"

#include "LuxSpriteRenderer.h"

virtual_table_type(Component) virtual_table_instance(SpriteRenderer_Component) = {
    (Component_Delete_Type)SpriteRenderer_Delete
};
virtual_table_type(Renderer) virtual_table_instance(SpriteRenderer_Renderer) = {
    (Renderer_Render_Type)SpriteRenderer_Render
};
component_no_destructor_implementations(SpriteRenderer, (Sprite *sprite, byte mask), (sprite, mask),
    (
        Renderer_Constructor(gameObject, &this->Renderer, &virtual_table_instance(SpriteRenderer_Component), &virtual_table_instance(SpriteRenderer_Renderer));
        this->sprite = sprite;
        this->mask = mask;
    )
)

void SpriteRenderer_Render(SpriteRenderer *this, Transform *transform) {
    Screen_DrawSprite(this->sprite, this->mask, transform->position.x, transform->position.y);
}
