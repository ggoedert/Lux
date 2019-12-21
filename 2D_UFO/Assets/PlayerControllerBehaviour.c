#include "LuxEngine.h"
#include "LuxSceneManagement.h"

#include "PlayerControllerBehaviour.h"

virtual_table(Component) virtual_table_instance(Component_PlayerControllerBehaviour) = {
    (Component_Delete_Type)PlayerControllerBehaviour_Delete
};
virtual_table(CustomBehaviour) virtual_table_instance(CustomBehaviour_PlayerControllerBehaviour) = {
    (CustomBehaviour_Start_Type)PlayerControllerBehaviour_Start,
    (CustomBehaviour_Update_Type)PlayerControllerBehaviour_Update
};
derived_class_simple_default_implementations(PlayerControllerBehaviour, CustomBehaviour, (&virtual_table_instance(Component_PlayerControllerBehaviour), &virtual_table_instance(CustomBehaviour_PlayerControllerBehaviour)))

void PlayerControllerBehaviour_Start(PlayerControllerBehaviour *this) {
    Debug_Log("PlayerControllerBehaviour_Start $%04x", this);
    this->updatetimes = 3;
}

void PlayerControllerBehaviour_Update(PlayerControllerBehaviour *this) {
    if (this->updatetimes) {
        Debug_Log("PlayerControllerBehaviour_Update $%04x - %d", this, this->updatetimes);
        this->updatetimes--;
    }
    /*if (!this->updatetimes)
        SceneManager_LoadScene(EndGameScene_Load);*/
}
