#include "Scene.h"
#include "GameObject.h"

#include "LuxGameObject.h"
#include "LuxCustomBehaviour.h"

#include "LuxDebug.h"

class_default_implementations(GameObject, (word id), (id),
    (
        Object_Constructor(&this->Object, id);
        Stack_Constructor(&this->componentPtrs, sizeof(Component *));
        Scene_RegisterGameObject(this);
    ),
    (
        int i;
        Component *component;
        for (i=0; i<this->componentPtrs.count; i++) {
            component = *(Component **)Stack_Get(&this->componentPtrs, i);
            component->vtable->Delete(component);
        }
    )
)

void GameObject_Run(GameObject *this) {
    int i;
    CustomBehaviour *customBehaviour;
    for (i=0; i<this->componentPtrs.count; i++) {
        customBehaviour = *(CustomBehaviour **)Stack_Get(&this->componentPtrs, i);
        customBehaviour->vtable->Update(customBehaviour);
    }
}
