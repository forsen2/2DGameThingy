// sprite.h 
#ifndef SPRITE_H
#define SPRITE_H

#include "raylib.h"

#define MAX_FRAMES 4
#define MAX_ANIMATION_SPEED 8


typedef struct
{
	Vector2 position;
	Color playerColor;
	Texture2D texture;
	Rectangle frameRec[MAX_FRAMES];
	int currentFrame;
	int framesCounter;
	int framesSpeed;

}Player;

void InitSprite(Player *player);
void AnimateSprite(Player *player);
void DrawSprite(Player *player);

#endif// SPRITE_H