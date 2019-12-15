#include "Scene.h"
#include "GameObject.h"

#include "LuxGameObject.h"
#include "LuxCustomBehaviour.h"

#include "LuxDebug.h"

class_default_implementations(GameObject, (word id), (id),
    (
        Object_Constructor(&this->Object, id);
        List_Constructor(&this->components, sizeof(Component *));
        Scene_RegisterGameObject(this);
    ),
    (
        int i;
        Component *component;
        for (i=0; i<this->components.count; i++) {
            component = *(Component **)List_Item(&this->components, i);
            component->vtable->Delete(component);
        }
    )
)

void GameObject_Run(GameObject *this) {
    int i;
    CustomBehaviour *customBehaviour;
    for (i=0; i<this->components.count; i++) {
        customBehaviour = *(CustomBehaviour **)List_Item(&this->components, i);
        customBehaviour->vtable->Update(customBehaviour);
    }
}
