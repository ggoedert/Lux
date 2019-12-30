#ifndef LUX_SPRITERENDERER_H
#define LUX_SPRITERENDERER_H

#include "LuxRenderer.h"

derived_class (SpriteRenderer, Renderer,
    NONE
);
class_default_prototypes(SpriteRenderer, virtual_table_type(Component) *vtable);

#endif
