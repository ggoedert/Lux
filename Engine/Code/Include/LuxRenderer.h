#ifndef LUX_RENDERER_H
#define LUX_RENDERER_H

#include "LuxComponent.h"

#define sortingLayer_Default 127

derived_class (Renderer, Component,
    bool enabled;
    byte sortingLayer;
);
class_default_prototypes(Renderer, virtual_table_type(Component) *vtable);

#endif
