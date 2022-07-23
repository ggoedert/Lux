#include "LuxTransform.h"

virtual_table_type(Component) virtual_table_instance(Transform_Component) = {
    (Component_Delete_Type)Transform_Delete
};
component_no_destructor_implementations(Transform, (VOID), (NONE),
    (
        Component_Constructor(gameObject, &this->Component, typeof_Transform, &virtual_table_instance(Transform_Component));
        this->position.x = 0;
        this->position.y = 0;
    )
)
