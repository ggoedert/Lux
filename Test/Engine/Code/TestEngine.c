#include "LuxEngine.h"
#include "LuxCustomBehaviour.h"
#include "LuxStorage.h"

void loadApplication(void);

derived_class (PlayerControllerBehaviour, CustomBehaviour,
    int updates, lastSecs;
);
class_default_prototypes(PlayerControllerBehaviour, VOID);
void PlayerControllerBehaviour_Start(PlayerControllerBehaviour *this);
void PlayerControllerBehaviour_Update(PlayerControllerBehaviour *this);

//main.c
void main() {
    Application_Play("TestEngine", 1, loadApplication);
}

void loadApplication() {
    GameObject *Player;

    Screen_SetResolution(HGR, true, false);
    Player = GameObject_New(NONE);
    List_Add(&Player->components, PlayerControllerBehaviour *, PlayerControllerBehaviour_New(NONE));
}

virtual_table_type(Object) virtual_table_instance(PlayerControllerBehaviour_Object) = {
    (Object_Delete_Type)PlayerControllerBehaviour_Delete
};
virtual_table_type(CustomBehaviour) virtual_table_instance(PlayerControllerBehaviour_CustomBehaviour) = {
    (CustomBehaviour_Start_Type)PlayerControllerBehaviour_Start,
    (CustomBehaviour_Update_Type)PlayerControllerBehaviour_Update
};
derived_class_simple_default_implementations(PlayerControllerBehaviour, CustomBehaviour, (&virtual_table_instance(PlayerControllerBehaviour_Object), &virtual_table_instance(PlayerControllerBehaviour_CustomBehaviour)))

void PlayerControllerBehaviour_Start(PlayerControllerBehaviour *this) {
    this->updates = 0;
    this->lastSecs = -1;
 }

void PlayerControllerBehaviour_Update(PlayerControllerBehaviour *this) {
    int secs = this->updates++/60;
    if (secs != this->lastSecs) {
        Camera_backgroundColor = secs&0xf;
        Screen_Clear();
        this->lastSecs = secs;
    }
}
