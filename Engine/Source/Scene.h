#ifndef SCENE_H
#define SCENE_H

#include "LuxGameObject.h"

void Scene_Init();
void Scene_Unload();
void Scene_RegisterGameObject(GameObject *gameObject);
void Scene_UnregisterGameObject(GameObject *gameObject);
void Scene_Run();

#endif
