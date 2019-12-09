#include "LuxScene.h"

void Scene_Constructor(Scene *this, virtual_table(Scene) *vtable, char *name) {
    this->vtable = vtable;
    this->name = name;
}

void Scene_Destructor(Scene *this) {
}
