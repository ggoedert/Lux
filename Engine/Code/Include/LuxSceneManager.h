#ifndef LUX_SCENE_MANAGER_H
#define LUX_SCENE_MANAGER_H

#include "LuxScene.h"

void SceneManager_IncludeScene(char *sceneName, Scene_Load scene_Load);
void SceneManager_LoadScene(char *sceneName);
void SceneManager_Run();

#endif
