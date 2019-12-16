#include "SceneManager.h"
#include "Scene.h"

#include "LuxSceneManager.h"


void SceneManager_Init() {
    Scene_Init();
}

void SceneManager_LoadScene(Scene_Load scene_Loader) {
    Scene_Finalize();
    Scene_Loader = scene_Loader;
    Scene_Loader();
}
