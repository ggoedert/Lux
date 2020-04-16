#ifndef LUX_COMPONENT_H
#define LUX_COMPONENT_H

#include "LuxObject.h"

// @@REVIEW@@ REMOVE THIS CLASS AND JUST USE OBJECT?
derived_class (Component, Object, EMPTY);
class_default_prototypes(Component, byte type, virtual_table_type(Object) *vtable);

#endif
