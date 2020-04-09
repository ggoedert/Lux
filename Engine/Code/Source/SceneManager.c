#include "Scene.h"

#include "LuxSceneManager.h"

void SceneManager_LoadScene(Scene_Load scene_Loader) {
    Scene_Unload();
    scene_Loader();
}
