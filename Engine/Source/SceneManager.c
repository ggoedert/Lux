#include "Scene.h"

#include "LuxSceneManager.h"

void SceneManager_LoadScene(Scene_Load scene_Load) {
    Scene_Unload();
    scene_Load();
}
