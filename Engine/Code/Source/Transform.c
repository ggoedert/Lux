#include "LuxTransform.h"

virtual_table_type(Object) virtual_table_instance(Transform_Object) = {
    (Object_Delete_Type)Transform_Delete
};
class_default_implementations(Transform, (VOID), (NONE),
    (
        Component_Constructor(&this->Component, typeof_Transform, &virtual_table_instance(Transform_Object));
        Vector2_Constructor(&this->position, NONE);
    ),
    (
        Component_Destructor(&this->Component);
    )
)
