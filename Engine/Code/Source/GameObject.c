#include "Scene.h"
#include "GameObject.h"

#include "LuxGameObject.h"
#include "LuxCustomBehaviour.h"
#include "LuxTransform.h"

#include "LuxDebug.h"

class_default_implementations(GameObject, (word id), (id),
    (
        Object_Constructor(&this->Object, id);
        List_Constructor(&this->components, sizeof(Component *));
        *(Transform **)List_Add(&this->components) = Transform_New();
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
    Component *component;
    for (i=0; i<this->components.count; i++) {
        component = *(Component **)List_Item(&this->components, i);
        if (component->Object.id == CUSTOMBEHAVIOUR_TYPE)
            ((CustomBehaviour *)component)->vtable->Update((CustomBehaviour *)component);
    }
}
