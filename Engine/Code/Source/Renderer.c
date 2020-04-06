#include "LuxRenderer.h"

class_constructor_destructor_implementations(Renderer, (virtual_table_type(Component) *component_vtable, virtual_table_type(Renderer) *renderer_vtable),
    (
        Component_Constructor(&this->Component, component_vtable, RendererType);
        this->vtable = renderer_vtable;
        this->enabled = true;
        this->sortingLayer = sortingLayer_Default;
    ),
    (
        Component_Destructor(&this->Component);
    )
)
