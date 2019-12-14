#ifndef SCENE_H
#define SCENE_H

#include "LuxGameObject.h"

void Scene_Init();
void Scene_Finalize();
void Scene_RegisterGameObject(GameObject *gameObject);
void Scene_Run();

#endif
