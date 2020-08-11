#ifndef PLAYER_CONTROLLER_BEHAVIOUR_H
#define PLAYER_CONTROLLER_BEHAVIOUR_H

#include "LuxCustomBehaviour.h"

derived_class (PlayerControllerBehaviour, CustomBehaviour,
    int updates, lastSecs;
);
derived_custom_behaviour_class_default_prototypes(PlayerControllerBehaviour);
void PlayerControllerBehaviour_Start(GameObject *gameObject, PlayerControllerBehaviour *this);
void PlayerControllerBehaviour_Update(GameObject *gameObject, PlayerControllerBehaviour *this);

#endif
