#include "LuxEngine.h"
#include "LuxSceneManagement.h"

#include "PlayerControllerBehaviour.h"

derived_custom_behaviour_class_default_implementations(PlayerControllerBehaviour, PlayerControllerBehaviour_Start, PlayerControllerBehaviour_Update, nullptr)

void PlayerControllerBehaviour_Start(GameObject *gameObject, PlayerControllerBehaviour *this) {
    GameObject_transform(gameObject)->position.x = 0;
    GameObject_transform(gameObject)->position.y = 0;
    this->updates = 0;
    this->lastSecs = -1;
}

void PlayerControllerBehaviour_Update(GameObject *gameObject, PlayerControllerBehaviour *this) {
    int secs = this->updates++/60;
    GameObject_transform(gameObject)->position.x = this->updates;
    GameObject_transform(gameObject)->position.y = this->updates;
    if (secs != this->lastSecs) {
        Camera_backgroundColor = secs&0xf;
        //Camera_backgroundColor = white;
        Screen_Clear();
        Debug_Log("PlayerControllerBehaviour_Update %d", secs);
        this->lastSecs = secs;
#ifdef _DEBUG
        Application_Stop();
#endif
    }
}
