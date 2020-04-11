#include "LuxSystem.h"
#include "LuxEngine.h"
#include "LuxSceneManagement.h"

#include "Assets.h"

#include "MainScene.h"
#include "PlayerControllerBehaviour.h"

Asset Assets[] = {
    {0, 100}
};

void MainScene_Load() {
    GameObject *Player;
    SpriteRenderer *spriteRenderer;
    Debug_Log("MainScene_Load - $%04x", MainScene_Load);
    Player = GameObject_New();
    spriteRenderer = SpriteRenderer_New();
    spriteRenderer->sprite = (Sprite *)Resources_Load(UFO);
    List_Add(&Player->components, SpriteRenderer *, spriteRenderer);
    List_Add(&Player->components, PlayerControllerBehaviour *, PlayerControllerBehaviour_New());
}
