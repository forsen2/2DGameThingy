// sprite.h 
#ifndef SPRITE_H
#define SPRITE_H

#include "raylib.h"

#define MAX_FRAMES 4
#define MAX_ANIMATION_SPEED 8
#define KEY_W 87
#define KEY_A 65
#define KEY_D 68
#define KEY_S 83
#define KEY_RESET 08

typedef struct
{
    Vector2 position;
    Color playerColor;
    Rectangle frameRec;
    int currentFrame;
    int framesCounter;

} Player;

void InitSprite(Player *player);
void AnimateSprite(Player *player);
void DrawSprite(Player *player);

Texture2D loadPlayerSpriteSheet(Player *player);
void initSpriteConfig(Player* player, Texture2D* spriteSheet);
void addSpriteWatcher(Player* player);

#endif// SPRITE_H