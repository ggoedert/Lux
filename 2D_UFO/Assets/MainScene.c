#include "LuxSystem.h"
#include "LuxEngine.h"
#include "LuxSceneManagement.h"

#include "Assets.h"

#include "MainScene.h"
#include "PlayerControllerBehaviour.h"

//TODO IMPLEMENT COMMENTED PARTS
void MainScene_Load() {
    GameObject *Player;
    SpriteRenderer *spriteRenderer;
    Debug_Log("MainScene_Load - $%04x", MainScene_Load);
    Player = GameObject_New();
    spriteRenderer = SpriteRenderer_New();
    spriteRenderer->sprite = (Sprite *)Resources_Load(UFO);
    *(SpriteRenderer **)List_Add(&Player->components) = spriteRenderer;
    *(PlayerControllerBehaviour **)List_Add(&Player->components) = PlayerControllerBehaviour_New();
}
