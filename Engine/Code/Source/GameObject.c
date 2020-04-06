#include "Scene.h"
#include "GameObject.h"

#include "LuxGameObject.h"
#include "LuxCustomBehaviour.h"
#include "LuxRenderer.h"
#include "LuxTransform.h"

class_default_implementations(GameObject, (NONE), (NONE),
    (
        List_Constructor(&this->components, sizeof(Component *));
        List_Add(Transform, &this->components, Transform_New());
        Scene_RegisterGameObject(this);
    ),
    (
        int i;
        Component *component;
        for (i=0; i<this->components.count; i++) {
            component = List_Item(Component, &this->components, i);
            component->vtable->Delete(component);
        }
        List_Destructor(&this->components);
    )
)

void GameObject_Run(GameObject *this) {
    int i;
    Component *component;
    CustomBehaviour_Update_Type CustomBehaviour_Update;
    for (i=0; i<this->components.count; i++) {
        component = List_Item(Component, &this->components, i);
        if (component->type==CustomBehaviourType) {
            CustomBehaviour_Update = ((CustomBehaviour *)component)->vtable->Update;
            if (CustomBehaviour_Update)
                CustomBehaviour_Update((CustomBehaviour *)component);
        }
        else if (component->type==RendererType)
            ((Renderer *)component)->vtable->Render((Renderer *)component);
    }
}
