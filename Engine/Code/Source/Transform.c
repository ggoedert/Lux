#include "LuxTransform.h"

virtual_table_type(Object) virtual_table_instance(Object_Transform) = {
    (Object_Delete_Type)Transform_Delete
};
class_default_implementations(Transform, (VOID), (NONE),
    (
        Component_Constructor(&this->Component, typeof_Transform, &virtual_table_instance(Object_Transform));
        Vector2_Constructor(&this->position, NONE);
    ),
    (
        Component_Destructor(&this->Component);
    )
)
