#include "Scene.h"
#include "GameObject.h"

#include "LuxGameObject.h"
#include "LuxCustomBehaviour.h"
#include "LuxRenderer.h"
#include "LuxTransform.h"

class_default_implementations(GameObject, (VOID), (NONE),
    (
        Transform *transform = Transform_New(NONE);
        List_Constructor(&this->components, sizeof(Component *));
        List_Add(&this->components, Transform *, transform); // first component is always the transform
        Scene_RegisterGameObject(this);
    ),
    (
        int i;
        Component *component;
        Scene_UnregisterGameObject(this);
        i=this->components.count;
        while (i--) {
            component = List_Item(&this->components, Component *, i);
            ((Object *)component)->vtable->Delete(((Object *)component));
        }
        List_Destructor(&this->components);
    )
)

Component *GameObject_GetComponent(GameObject *this, byte type) {
    int i;
    Component *component;
    for (i=1; i<this->components.count; ++i) { // first component is always the transform
        component = List_Item(&this->components, Component *, i);
        if (component->Object.type == type)
            return component;
    }
    return nullptr;
}

void GameObject_Run(GameObject *this) {
    int i;
    Component *component;
    CustomBehaviour_Update_Type CustomBehaviour_Update;
    for (i=1; i<this->components.count; ++i) { // first component is always the transform
        component = List_Item(&this->components, Component *, i);
        if (component->Object.type == typeof_CustomBehaviour) {
            CustomBehaviour_Update = ((CustomBehaviour *)component)->vtable->Update;
            if (CustomBehaviour_Update)
                CustomBehaviour_Update(this, (CustomBehaviour *)component);
        }
        else if (component->Object.type == typeof_Renderer) {
            ((Renderer *)component)->vtable->Render((Renderer *)component, GameObject_transform(this));
        }
    }
}
