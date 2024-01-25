#include "raylib.h"
#include "include/sprite.h"
#include <stdio.h>


Texture2D loadPlayerSpriteSheet(Player *player) {
	const char* file = "C:/Users/olihb/Desktop/projects/2DCycleGame/models/sprite_sheets/player1.png";
	Image image = LoadImage(file);
	ImageResize(&image, 1841 / 4 - 250, 2400 / 5 - 250); // Assuming 4 columns and 5 rows

	Texture2D spriteSheet = LoadTextureFromImage(image);
	UnloadImage(image);
	return spriteSheet;
}

void initSpriteConfig(Player* player, Texture2D* spriteSheet) {
	player->frameRec = (Rectangle){ 15, 0, spriteSheet->width / 5 + 15, spriteSheet->height / 4 };
	player->currentFrame = 0;
	player->framesCounter = 0;

}

void addSpriteWatcher(Player* player) {
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_A) || IsKeyDown(KEY_W) || IsKeyDown(KEY_S))
    {
        player->framesCounter++;

        if (player->framesCounter >= (60 / 8))
        {
            player->framesCounter = 0;
            player->currentFrame++;

            if (player->currentFrame > 3) {
                player->currentFrame = 0;

                player->frameRec.x = (float)player->currentFrame * (float)player->frameRec.width;
               
            }
        }
    }
    else
    {
        player->framesCounter = 0;
        player->currentFrame = 0;
        player->frameRec.x = 0.0f;
    }
}