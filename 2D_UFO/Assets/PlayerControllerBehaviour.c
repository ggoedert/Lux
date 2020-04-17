#include "LuxEngine.h"
#include "LuxSceneManagement.h"

#include "PlayerControllerBehaviour.h"

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
        //Camera_backgroundColor = secs&0xf;
        //Screen_Clear();
        Debug_Log("PlayerControllerBehaviour_Update %d", secs);
        this->lastSecs = secs;
#ifdef _DEBUG
        Application_Stop();
#endif
    }
}
