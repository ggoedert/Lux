#ifndef SCENE_H
#define SCENE_H

#include "LuxGameObject.h"

void Scene_Init(void);
#ifdef _DEBUG
void Scene_Finalize(void);
#endif
void Scene_Unload(void);
void Scene_RegisterGameObject(GameObject *gameObject);
void Scene_UnregisterGameObject(GameObject *gameObject);
void Scene_Run(void);

#endif
