#ifndef LUX_ASSET_H
#define LUX_ASSET_H

#include "LuxObject.h"

derived_class (Asset, Object, NONE);
class_default_prototypes(Asset, byte type, virtual_table_type(Object) *vtable);

#endif
