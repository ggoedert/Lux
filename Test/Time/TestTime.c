#include <conio.h> 

#include "LuxEngine.h"
#include "LuxCustomBehaviour.h"

void loadApplication(void);

derived_class (PlayerControllerBehaviour, CustomBehaviour,
    int updates, lastSecs;
);
derived_custom_behaviour_class_default_prototypes(PlayerControllerBehaviour);
void PlayerControllerBehaviour_Start(GameObject *gameObject, PlayerControllerBehaviour *this);
void PlayerControllerBehaviour_Update(GameObject *gameObject, PlayerControllerBehaviour *this);

//main.c
void main() {
    Application_Play("TestTime", 1, loadApplication);
}

void loadApplication() {
    GameObject *Player;

    Screen_SetResolution(TEXT, false, false);
    Debug_SetMode(DEBUG_MODE_CONSOLE);
    Player = GameObject_New(NONE);
    List_Add(&Player->components, PlayerControllerBehaviour *, PlayerControllerBehaviour_New(NONE));
}

derived_custom_behaviour_class_default_implementations(PlayerControllerBehaviour, PlayerControllerBehaviour_Start, PlayerControllerBehaviour_Update, nullptr)

void PlayerControllerBehaviour_Start(GameObject *gameObject, PlayerControllerBehaviour *this) {
    this->updates = 0;
    this->lastSecs = -1;
 }

void PlayerControllerBehaviour_Update(GameObject *gameObject, PlayerControllerBehaviour *this) {
    int secs = this->updates++/60;
    if (secs != this->lastSecs) {
        gotoy(-1);
        Debug_Log("Time = %d", secs);
        this->lastSecs = secs;
    }
}
