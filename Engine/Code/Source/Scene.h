#ifndef SCENE_H
#define SCENE_H

#include "LuxGameObject.h"

extern List gameObjectList;
void Scene_Init(void);
void Scene_Finalize(void);
void Scene_RegisterGameObject(GameObject *gameObject);
void Scene_Run(void);

#endif
