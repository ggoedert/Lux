#include "LuxEngine.h"
#include "LuxSceneManagement.h"

#include "PlayerControllerBehaviour.h"

#define HGR_WIDTH  140
#define HGR_HEIGHT 192

derived_custom_behaviour_class_default_implementations(PlayerControllerBehaviour, PlayerControllerBehaviour_Start, PlayerControllerBehaviour_Update, nullptr)

void PlayerControllerBehaviour_Start(GameObject *gameObject, PlayerControllerBehaviour *this) {
    SpriteRenderer *spriteRenderer;
    GameObject_transform(gameObject)->position.x = 0;
    GameObject_transform(gameObject)->position.y = 0;
    this->updates = 0;
    this->lastSecs = -1;
    spriteRenderer = (SpriteRenderer *)GameObject_GetComponent(gameObject, typeof_Renderer);
    this->spriteWidth = spriteRenderer->sprite->width;
    this->spriteHeight = spriteRenderer->sprite->height;
    this->xPositive = true;
    this->yPositive = true;
}

void PlayerControllerBehaviour_Update(GameObject *gameObject, PlayerControllerBehaviour *this) {
    int secs = this->updates++/60, extra;
    int x = GameObject_transform(gameObject)->position.x;
    int y = GameObject_transform(gameObject)->position.y;

    if (this->xPositive) {
        x++;
        extra = (x+this->spriteWidth)-HGR_WIDTH;
        if (extra > 0) {
            x -= extra*2;
            this->xPositive = false;
        }
    }
    else {
        if (x) {
            x--;
            extra = -x;
            if (extra > 0) {
                x = extra;
                this->xPositive = true;
            }
        }
        else {
            x = 1;
            this->xPositive = true;
        }
    }

    if (this->yPositive) {
        y++;
        extra = (y+this->spriteHeight)-HGR_HEIGHT;
        if (extra > 0) {
            y -= extra*2;
            this->yPositive = false;
        }
    }
    else {
        if (y) {
            y--;
            extra = -y;
            if (extra > 0) {
                y = extra;
                this->yPositive = true;
            }
        }
        else {
            y = 1;
            this->yPositive = true;
        }
    }

    GameObject_transform(gameObject)->position.x = x;
    GameObject_transform(gameObject)->position.y = y;

    if (secs != this->lastSecs) {
        Camera_backgroundColor = secs&0xf;
        //Camera_backgroundColor = white;
        Screen_Clear();
        Debug_Log("PlayerControllerBehaviour_Update %d", secs);
        this->lastSecs = secs;
#ifdef _DEBUG
        Application_Stop(); //run only once
#endif
    }
}
