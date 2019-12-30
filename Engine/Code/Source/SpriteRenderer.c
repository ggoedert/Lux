#include "LuxSpriteRenderer.h"

class_default_implementations(SpriteRenderer, (virtual_table_type(Component) *vtable), (vtable),
    (
        Renderer_Constructor(&this->Renderer, vtable);
    ),
    (
        Renderer_Destructor(&this->Renderer);
    )
)
