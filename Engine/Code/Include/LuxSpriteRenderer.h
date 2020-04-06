#ifndef LUX_SPRITERENDERER_H
#define LUX_SPRITERENDERER_H

#include "LuxRenderer.h"
#include "LuxSprite.h"

derived_class (SpriteRenderer, Renderer,
    Sprite *sprite;
);
class_default_prototypes(SpriteRenderer, NONE);
void SpriteRenderer_Update(SpriteRenderer *this);

#endif
