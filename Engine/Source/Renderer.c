#include "LuxRenderer.h"

component_constructor_destructor_implementations(Renderer, (virtual_table_type(Component) *component_vtable, virtual_table_type(Renderer) *renderer_vtable),
    (
        Component_Constructor(gameObject, &this->Component, typeof_Renderer, component_vtable);
        this->vtable = renderer_vtable;
        this->enabled = true;
        this->sortingLayer = sortingLayer_Default;
    ),
    (
        EMPTY
    )
)
