#include "LuxSystem.h"
#include "LuxEngine.h"
#include "LuxSceneManagement.h"

#include "Assets.h"
#include "MainScene.h"
#include "PlayerControllerBehaviour.h"

void MainScene_Load() {
    GameObject *Player;
    Debug_Log("MainScene_Load - $%04x", MainScene_Load);
    Player = GameObject_New(NONE);
    List_Add(&Player->components, SpriteRenderer *, SpriteRenderer_New((Sprite *)Resources_Reference(UFO)));
    List_Add(&Player->components, PlayerControllerBehaviour *, PlayerControllerBehaviour_New(NONE));
}
