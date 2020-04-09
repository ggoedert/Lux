#include "LuxEngine.h"
#include "LuxSceneManagement.h"

#include "PlayerControllerBehaviour.h"

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
        //Camera_backgroundColor = secs&0xf;
        //Screen_Clear();
        Debug_Log("PlayerControllerBehaviour_Update %d", secs);
        this->lastSecs = secs;
#ifdef _DEBUG
        Application_Stop();
#endif
    }
}
