#include "LuxSpriteRenderer.h"

virtual_table_type(Component) virtual_table_instance(Component_SpriteRenderer) = {
    (Component_Delete_Type)SpriteRenderer_Delete
};
virtual_table_type(Renderer) virtual_table_instance(Renderer_SpriteRenderer) = {
    (Renderer_Render_Type)SpriteRenderer_Render
};
derived_class_simple_default_implementations(SpriteRenderer, Renderer, (&virtual_table_instance(Component_SpriteRenderer), &virtual_table_instance(Renderer_SpriteRenderer)))

#include "LuxDebug.h"
void SpriteRenderer_Render(SpriteRenderer *this) {
    Debug_Log("SpriteRenderer_Render");
    //TODO!!!
}
