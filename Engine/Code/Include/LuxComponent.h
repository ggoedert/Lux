#ifndef LUX_COMPONENT_H
#define LUX_COMPONENT_H

#include "LuxObject.h"

derived_class (Component, Object, NONE);
class_default_prototypes(Component, byte type, virtual_table_type(Object) *vtable);

#endif
