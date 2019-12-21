#ifndef PLAYER_CONTROLLER_BEHAVIOUR_H
#define PLAYER_CONTROLLER_BEHAVIOUR_H

#include "LuxCustomBehaviour.h"

derived_class (PlayerControllerBehaviour, CustomBehaviour,
    int updatetimes;
);
class_default_prototypes(PlayerControllerBehaviour, NONE);
void PlayerControllerBehaviour_Start(PlayerControllerBehaviour *this);
void PlayerControllerBehaviour_Update(PlayerControllerBehaviour *this);

#endif
