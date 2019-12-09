#include <stdlib.h>
#include <string.h>

#include "SceneManager.h"

#include "LuxSceneManager.h"
#include "LuxStack.h"

typedef struct {
    char *sceneName;
    Scene_Load scene_Load;
} SceneManagerItem;

Stack sceneManagerStack;
Scene *activeScene = nullptr;                                                           //SHOULD NOT NEED THIS, GAME SHOULD WORK EVEN WITHOUT A SCENE LOADED

void SceneManager_Init() {
    Stack_Constructor(&sceneManagerStack, sizeof(SceneManagerItem));
}

void SceneManager_IncludeScene(char *sceneName, Scene_Load scene_Load) {
    SceneManagerItem *sceneManagerItem = Stack_Push(&sceneManagerStack);
    sceneManagerItem->sceneName = sceneName;
    sceneManagerItem->scene_Load = scene_Load;
}

void SceneManager_Run() {
    if ((activeScene == nullptr) && sceneManagerStack.count) {                          //SHOULD NOT NEED THIS, GAME SHOULD WORK EVEN WITHOUT A SCENE LOADED
        SceneManagerItem *sceneManagerItem = Stack_Get(&sceneManagerStack, 0);
        activeScene = sceneManagerItem->scene_Load(sceneManagerItem->sceneName);
    }
    
//    if (activeScene != nullptr)
//        activeScene->vtable->Run(activeScene);                                          //SHOULD NOT NEED THIS, RUN SHOULD ONLY GO THROGH THE LIST OF CURRENT GAMEOBJECTS
}
