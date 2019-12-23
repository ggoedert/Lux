#include <conio.h> 

#include "LuxEngine.h"

#include "LuxCustomBehaviour.h"

void loadApplication(void);

derived_class (PlayerControllerBehaviour, CustomBehaviour, NONE);
class_default_prototypes(PlayerControllerBehaviour, NONE);
void PlayerControllerBehaviour_Start(PlayerControllerBehaviour *this);
void PlayerControllerBehaviour_Update(PlayerControllerBehaviour *this);

//main.c
void main() {
    _heapadd((void *)0x800, 0x1800);
    Application_Run("TestFloat", 1, loadApplication);
}

void loadApplication() {
    Float frameTime;
    char buffer[FLOAT_MAX_STRING_SIZE];
    GameObject *Player;

    Debug_SetMode(DEBUG_MODE_CONSOLE);
    Screen_SetResolution(TEXT, false, false);
    Player = GameObject_New();
    *(PlayerControllerBehaviour **)List_Add(&Player->components) = PlayerControllerBehaviour_New();
}

virtual_table(Component) virtual_table_instance(Component_PlayerControllerBehaviour) = {
    (Component_Delete_Type)PlayerControllerBehaviour_Delete
};
virtual_table(CustomBehaviour) virtual_table_instance(CustomBehaviour_PlayerControllerBehaviour) = {
    (CustomBehaviour_Start_Type)PlayerControllerBehaviour_Start,
    (CustomBehaviour_Update_Type)PlayerControllerBehaviour_Update
};
derived_class_simple_default_implementations(PlayerControllerBehaviour, CustomBehaviour, (&virtual_table_instance(Component_PlayerControllerBehaviour), &virtual_table_instance(CustomBehaviour_PlayerControllerBehaviour)))

void PlayerControllerBehaviour_Start(PlayerControllerBehaviour *this) {}

void PlayerControllerBehaviour_Update(PlayerControllerBehaviour *this) {
    int clock = Time_clock_Get();
    if (clock%1000 == 0) {
        gotoy(-1);
        Debug_Log("Time = %d", clock);
    }
    /*//char buffer[FLOAT_MAX_STRING_SIZE];

    gotoy(-1);
    //Float_ToString(Time_ToTime(Time_clock_Get()), buffer, 5);
    //Debug_Log("Time = %s", buffer);
    //Debug_Log("Time = %d", Time_clock_Get()/30);
    Debug_Log("Time = %d", Time_clock_Get());*/
}
