#ifndef LUX_RENDERER_H
#define LUX_RENDERER_H

#include "LuxTransform.h"
#include "LuxComponent.h"

#define typeof_Renderer 0x3a // String_GetHashCode8("Renderer")

derived_virtual_class(Renderer, Component,
    (
        bool enabled;
        byte sortingLayer;
    ),
    (
        void (*Render)(Renderer *this, Transform *transform);
    )
);
typedef void (*Renderer_Render_Type)(Renderer *this, Transform *transform);
component_constructor_destructor_prototypes(Renderer, virtual_table_type(Component) *component_vtable, virtual_table_type(Renderer) *renderer_vtable);

#define sortingLayer_Default 127

#endif
