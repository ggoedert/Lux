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
    Scene_Init();
}

void SceneManager_IncludeScene(word sceneId, Scene_Load scene_Load) {
    SceneManagerItem *sceneManagerItem = Stack_Push(&sceneManagerStack);
    sceneManagerItem->sceneId = sceneId;
    sceneManagerItem->scene_Load = scene_Load;
}

void SceneManager_LoadScene(word sceneId) {
    int i;
    for (i=0; i<sceneManagerStack.count; i++) {
        SceneManagerItem *sceneManagerItem = Stack_Get(&sceneManagerStack, i);
        if (sceneManagerItem->sceneId == sceneId) {
            Scene_Finalize();
            Scene_id = sceneId;
            sceneManagerItem->scene_Load();
            break;
        }
    }
}

