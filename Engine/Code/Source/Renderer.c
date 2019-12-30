#include "LuxRenderer.h"

class_default_implementations(Renderer, (virtual_table_type(Component) *vtable), (vtable),
    (
        Component_Constructor(&this->Component, vtable);
        this->enabled = true;
        this->sortingLayer = sortingLayer_Default;
    ),
    (
        Component_Destructor(&this->Component);
    )
)
