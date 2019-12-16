#include "Scene.h"

#include "LuxSceneManager.h"

void SceneManager_LoadScene(Scene_Load scene_Loader) {
    Scene_Finalize();
    scene_Loader();
}
