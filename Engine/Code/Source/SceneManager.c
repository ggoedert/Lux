#include "SceneManager.h"
#include "Scene.h"

#include "LuxSceneManager.h"
#include "LuxCollections.h"

typedef struct {
    word sceneId;
    Scene_Load scene_Load;
} SceneManagerItem;

List sceneManagerList;

void SceneManager_Init() {
    List_Constructor(&sceneManagerList, sizeof(SceneManagerItem));
    Scene_Init();
}

void SceneManager_IncludeScene(word sceneId, Scene_Load scene_Load) {
    SceneManagerItem *sceneManagerItem = List_Add(&sceneManagerList);
    sceneManagerItem->sceneId = sceneId;
    sceneManagerItem->scene_Load = scene_Load;
}

void SceneManager_LoadScene(word sceneId) {
    int i;
    for (i=0; i<sceneManagerList.count; i++) {
        SceneManagerItem *sceneManagerItem = List_Item(&sceneManagerList, i);
        if (sceneManagerItem->sceneId == sceneId) {
            Scene_Finalize();
            Scene_id = sceneId;
            sceneManagerItem->scene_Load();
            break;
        }
    }
}

