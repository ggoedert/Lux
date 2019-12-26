#include "LuxTransform.h"

virtual_table_type(Component) virtual_table_instance(Component_Transform) = {
    (Component_Delete_Type)Transform_Delete
};
class_default_implementations(Transform, (NONE), (NONE),
    (
        Component_Constructor(&this->Component, &virtual_table_instance(Component_Transform));
        Vector2_Constructor(&this->position);
    ),
    (
        Component_Destructor(&this->Component);
    )
)
