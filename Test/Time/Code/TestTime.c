#include <conio.h> 

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
    Application_Play("TestFloat", 1, loadApplication);
}

void loadApplication() {
    GameObject *Player;

    Screen_SetResolution(TEXT, false, false);
    Debug_SetMode(DEBUG_MODE_CONSOLE);
    Player = GameObject_New();
    List_Add(&Player->components, PlayerControllerBehaviour *, PlayerControllerBehaviour_New());
}

virtual_table_type(Object) virtual_table_instance(Object_PlayerControllerBehaviour) = {
    (Object_Delete_Type)PlayerControllerBehaviour_Delete
};
virtual_table_type(CustomBehaviour) virtual_table_instance(CustomBehaviour_PlayerControllerBehaviour) = {
    (CustomBehaviour_Start_Type)PlayerControllerBehaviour_Start,
    (CustomBehaviour_Update_Type)PlayerControllerBehaviour_Update
};
derived_class_simple_default_implementations(PlayerControllerBehaviour, CustomBehaviour, (&virtual_table_instance(Object_PlayerControllerBehaviour), &virtual_table_instance(CustomBehaviour_PlayerControllerBehaviour)))

void PlayerControllerBehaviour_Start(PlayerControllerBehaviour *this) {
    this->updates = 0;
    this->lastSecs = -1;
 }

void PlayerControllerBehaviour_Update(PlayerControllerBehaviour *this) {
    int secs = this->updates++/60;
    if (secs != this->lastSecs) {
        gotoy(-1);
        Debug_Log("Time = %d", secs);
        this->lastSecs = secs;
    }
}
