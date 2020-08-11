#ifndef LUX_SPRITERENDERER_H
#define LUX_SPRITERENDERER_H

#include "LuxRenderer.h"
#include "LuxSprite.h"

derived_class (SpriteRenderer, Renderer,
    Sprite *sprite;
);
class_default_prototypes(SpriteRenderer, Sprite *sprite);
void SpriteRenderer_Render(SpriteRenderer *this, Transform *transform);

#endif
