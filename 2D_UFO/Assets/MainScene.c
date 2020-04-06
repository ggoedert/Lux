#include "LuxSystem.h"
#include "LuxEngine.h"
#include "LuxSceneManagement.h"

#include "Assets.h"

#include "MainScene.h"
#include "PlayerControllerBehaviour.h"

Asset Assets[] = {
    {0, 100}
};

//TODO IMPLEMENT COMMENTED PARTS
void MainScene_Load() {
    GameObject *Player;
    SpriteRenderer *spriteRenderer;
    Debug_Log("MainScene_Load - $%04x", MainScene_Load);
    Player = GameObject_New();
    spriteRenderer = SpriteRenderer_New();
    spriteRenderer->sprite = (Sprite *)Resources_Load(UFO);
    List_Add(SpriteRenderer, &Player->components, spriteRenderer);
    List_Add(PlayerControllerBehaviour, &Player->components, PlayerControllerBehaviour_New());
}
