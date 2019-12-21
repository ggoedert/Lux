#include "LuxSystem.h"
#include "LuxEngine.h"
#include "LuxSceneManagement.h"

#include "MainScene.h"
#include "PlayerControllerBehaviour.h"

void MainScene_Load() {
    GameObject *Player;
    Debug_Log("MainScene_Load - $%04x", MainScene_Load);
    Player = GameObject_New();
    *(PlayerControllerBehaviour **)List_Add(&Player->components) = PlayerControllerBehaviour_New();
}
