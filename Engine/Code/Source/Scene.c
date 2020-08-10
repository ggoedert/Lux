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

#ifdef _DEBUG
void Scene_Finalize() {
    Scene_Unload();
    List_Destructor(&gameObjectList);
}
#endif

void Scene_Unload() {
    int i;
    i=gameObjectList.count;
    while (i--)
        GameObject_Delete(List_Item(&gameObjectList, GameObject *, i));
    List_Clear(&gameObjectList);
}

void Scene_RegisterGameObject(GameObject *gameObject) {
    List_Add(&gameObjectList, GameObject *, gameObject);
}

void Scene_UnregisterGameObject(GameObject *gameObject) {
    List_Remove(&gameObjectList, gameObject);
}

void Scene_Run() {
    int i;
    for (i=0; i<gameObjectList.count; i++) {
        GameObject_Run(List_Item(&gameObjectList, GameObject *, i));
        Time_Update();
    }
    if (i==0)
        Time_Update();
}
