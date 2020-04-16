#include "Scene.h"
#include "GameObject.h"

#include "LuxGameObject.h"
#include "LuxCustomBehaviour.h"
#include "LuxRenderer.h"
#include "LuxTransform.h"

class_default_implementations(GameObject, (VOID), (NONE),
    (
        List_Constructor(&this->components, sizeof(Component *));
        List_Add(&this->components, Transform *, Transform_New(NONE));
        Scene_RegisterGameObject(this);
    ),
    (
        int i;
        Component *component;
        for (i=0; i<this->components.count; i++) {
            component = List_Item(&this->components, Component *, i);
            ((Object *)component)->vtable->Delete(((Object *)component));
        }
        List_Destructor(&this->components);
    )
)

void GameObject_Run(GameObject *this) {
    int i;
    Component *component;
    CustomBehaviour_Update_Type CustomBehaviour_Update;
    for (i=0; i<this->components.count; i++) {
        component = List_Item(&this->components, Component *, i);
        if (component->Object.type == typeof_CustomBehaviour) {
            CustomBehaviour_Update = ((CustomBehaviour *)component)->vtable->Update;
            if (CustomBehaviour_Update)
                CustomBehaviour_Update((CustomBehaviour *)component);
        }
        else if (component->Object.type == typeof_Renderer)
            ((Renderer *)component)->vtable->Render((Renderer *)component);
    }
}
