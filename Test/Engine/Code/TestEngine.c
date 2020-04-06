#include "LuxEngine.h"
#include "LuxCustomBehaviour.h"

void loadApplication(void);

derived_class (PlayerControllerBehaviour, CustomBehaviour,
    int updates, lastSecs;
);
class_default_prototypes(PlayerControllerBehaviour, NONE);
void PlayerControllerBehaviour_Start(PlayerControllerBehaviour *this);
void PlayerControllerBehaviour_Update(PlayerControllerBehaviour *this);

//main.c
void main() {
    _heapadd((void *)0x800, 0x1800);
    Application_Run("TestEngine", 1, loadApplication);
}

void loadApplication() {
    GameObject *Player;

    Screen_SetResolution(HGR, true, false);
    Player = GameObject_New();
    List_Add(PlayerControllerBehaviour, &Player->components, PlayerControllerBehaviour_New());
}

virtual_table_type(Component) virtual_table_instance(Component_PlayerControllerBehaviour) = {
    (Component_Delete_Type)PlayerControllerBehaviour_Delete
};
virtual_table_type(CustomBehaviour) virtual_table_instance(CustomBehaviour_PlayerControllerBehaviour) = {
    (CustomBehaviour_Start_Type)PlayerControllerBehaviour_Start,
    (CustomBehaviour_Update_Type)PlayerControllerBehaviour_Update
};
derived_class_simple_default_implementations(PlayerControllerBehaviour, CustomBehaviour, (&virtual_table_instance(Component_PlayerControllerBehaviour), &virtual_table_instance(CustomBehaviour_PlayerControllerBehaviour)))

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
