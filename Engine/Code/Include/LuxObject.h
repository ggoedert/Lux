#ifndef LUX_OBJECT_H
#define LUX_OBJECT_H

#include "LuxTypes.h"

virtual_class (Object,
    (
        NONE
    ),
    (
        void (*Delete)(Object *this);
    )
);
typedef void (*Object_Delete_Type)(Object *this);
class_default_prototypes(Object, virtual_table_type(Object) *vtable);

#endif
