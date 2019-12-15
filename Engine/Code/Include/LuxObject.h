#ifndef LUX_OBJECT_H
#define LUX_OBJECT_H

#include "LuxDefs.h"

class (Object,
    // @WARNING@ ids are used to manage Objects (currently used by GameObjects on the Scene)
    // @WARNING@ but are also being used to identify CustomBehaviours inside GameObjects
    // @WARNING@ a proper implementation would separate then
    word id;
    //word type;
);
class_default_prototypes(Object, word id);

#endif
