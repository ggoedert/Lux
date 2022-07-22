#include "LuxSystem.h"
#include "LuxEngine.h"
#include "LuxSceneManagement.h"

#include "Assets.h"
#include "MainScene.h"
#include "PlayerControllerBehaviour.h"

#ifndef __CC65__
Sprite *UFOSprite;
#endif

void MainScene_Load() {
    GameObject *Player;
#ifdef __CC65__
    Sprite *UFOSprite;
#endif
    Debug_Log("MainScene_Load - $%04x", MainScene_Load);
    Player = GameObject_New(NONE);
    UFOSprite = Sprite_New(ResourceUFO);
    List_Add(&Player->components, SpriteRenderer *, SpriteRenderer_New(Player, UFOSprite, -1));
    List_Add(&Player->components, PlayerControllerBehaviour *, PlayerControllerBehaviour_New(Player));
}

#ifndef __CC65__
void MainScene_Unload() {
    Scene_Finalize();
    Sprite_Delete(UFOSprite);
}
#endif
