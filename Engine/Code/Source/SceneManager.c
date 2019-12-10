#include <stdlib.h>
#include <string.h>

#include "SceneManager.h"
#include "Scene.h"

#include "LuxSceneManager.h"
#include "LuxStack.h"

typedef struct {
    word sceneId;
    Scene_Load scene_Load;
} SceneManagerItem;

Stack sceneManagerStack;

void SceneManager_Init() {
    Stack_Constructor(&sceneManagerStack, sizeof(SceneManagerItem));
}

void SceneManager_IncludeScene(word sceneId, Scene_Load scene_Load) {
    SceneManagerItem *sceneManagerItem = Stack_Push(&sceneManagerStack);
    sceneManagerItem->sceneId = sceneId;
    sceneManagerItem->scene_Load = scene_Load;
}

void SceneManager_Run() {
    if (sceneManagerStack.count) {                          //SHOULD NOT NEED THIS, GAME SHOULD WORK EVEN WITHOUT A SCENE LOADED
        SceneManagerItem *sceneManagerItem = Stack_Get(&sceneManagerStack, 0);
        sceneManagerItem->scene_Load(sceneManagerItem->sceneId);
    }
    
    /* ???
	if (activeScene != nullptr)
        activeScene->vtable->Run(activeScene);                                          //SHOULD NOT NEED THIS, RUN SHOULD ONLY GO THROGH THE LIST OF CURRENT GAMEOBJECTS
	??? */
}
