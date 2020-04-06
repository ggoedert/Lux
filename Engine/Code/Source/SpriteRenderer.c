#include "LuxSpriteRenderer.h"

virtual_table_type(Component) virtual_table_instance(Component_SpriteRenderer) = {
    (Component_Delete_Type)SpriteRenderer_Delete
};
virtual_table_type(Renderer) virtual_table_instance(Renderer_SpriteRenderer) = {
    (Renderer_Update_Type)SpriteRenderer_Update
};
derived_class_simple_default_implementations(SpriteRenderer, Renderer, (&virtual_table_instance(Component_SpriteRenderer), &virtual_table_instance(Renderer_SpriteRenderer)))

void SpriteRenderer_Update(SpriteRenderer *this) {
    //TODO!!!
}
