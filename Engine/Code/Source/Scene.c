#include "Scene.h"
#include "Time.h"
#include "GameObject.h"

#include "LuxSystem.h"
#include "LuxScene.h"
#include "LuxTime.h"
#include "LuxCustomBehaviour.h"

List gameObjectList;

void Scene_Init() {
    List_Constructor(&gameObjectList, sizeof(GameObject *));
}

void Scene_Finalize() {
    int i;
    for (i=0; i<gameObjectList.count; i++)
        GameObject_Delete(*(GameObject **)List_Item(&gameObjectList, i));
    List_Clear(&gameObjectList);
}

void Scene_RegisterGameObject(GameObject *gameObject) {
    *(GameObject **)List_Add(&gameObjectList) = gameObject;
}

void Scene_Run() {
    int i;
    for (i=0; i<gameObjectList.count; i++) {
        GameObject_Run(*(GameObject **)List_Item(&gameObjectList, i));
        Time_Update();
    }
    if (i==0)
        Time_Update();
}
