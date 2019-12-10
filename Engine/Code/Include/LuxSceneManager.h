#ifndef LUX_SCENE_MANAGER_H
#define LUX_SCENE_MANAGER_H

#include "LuxScene.h"

void SceneManager_IncludeScene(word sceneId, Scene_Load scene_Load);
void SceneManager_LoadScene(word sceneId);
void SceneManager_Run();

#endif
