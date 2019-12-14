#include "Scene.h"
#include "GameObject.h"

#include "LuxSystem.h"
#include "LuxScene.h"
#include "LuxCustomBehaviour.h"

Stack gameObjectStack;

void Scene_Init() {
    Scene_id = 0xBF4C/*String_GetHashCode("Untitled")*/;
    Stack_Constructor(&gameObjectStack, sizeof(GameObject *));
}

void Scene_Finalize() {
    int i;
    for (i=0; i<gameObjectStack.count; i++) {
        GameObject_Delete(*(GameObject **)Stack_Get(&gameObjectStack, i));
    }
    Stack_Clear(&gameObjectStack);
}

void Scene_RegisterGameObject(GameObject *gameObject) {
    *(GameObject **)Stack_Push(&gameObjectStack) = gameObject;
}

void Scene_Run() {
    int i;
    for (i=0; i<gameObjectStack.count; i++) {
        GameObject_Run(*(GameObject **)Stack_Get(&gameObjectStack, i));
    }
}
