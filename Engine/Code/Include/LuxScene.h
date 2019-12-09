#ifndef LUX_SCENE_H
#define LUX_SCENE_H

#include "LuxDefs.h"

virtual_class (Scene, ( //THIS ENTIRE CLASS SHOULD BE HIDDEN FROM THE APLICATION (OR BE A SIMPLER STATIC), ONLY MANAGING COLECTIUON OF GAMEOBJECTS, ONLY THE SCENE MANAGER SHOULD CALL LOAD / UNLOAD SCENES FROM THE APLICATION
		char *name;
    ), (
//???		void (*Run)(Scene *this);
    )
);
void Scene_Constructor(Scene *this, virtual_table(Scene) *vtable, char *name);
void Scene_Destructor(Scene *this);
typedef Scene *(*Scene_Load)(char *name);
//???typedef void (*Scene_Run)(Scene *this);   //SHOULD NOT HAVE A VIRTUAL SCENE RUN, ONLY AN INTERNAL ONE ENGINE THAT RUNS THE GAME OBJECTS

#endif
