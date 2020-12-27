#ifndef LUX_GAME_OBJECT_H
#define LUX_GAME_OBJECT_H

#include "LuxCollections.h"
#include "LuxComponent.h"

class (GameObject,
    List components;
);
class_new_delete_prototypes(GameObject, VOID);

#define GameObject_transform(this) (*(Transform **)this->components.items)
Component *GameObject_GetComponent(GameObject *this, byte type);

#endif
