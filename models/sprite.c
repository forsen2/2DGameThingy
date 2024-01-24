#include "../include/sprite.h"
#include "../include/raylib.h"

int currentFrame = 0;
float frameTime = 0.1f;
Texture2D playerSpriteSheet;



void InitSprite(Player* player) {
	const char* filename = "C:/Users/olihb/Desktop/projects/2DCycleGame/textures/level1/player_sprite.png";
	Image image = LoadImage(filename);
	player->texture = LoadTextureFromImage(image);
	UnloadImage(image);

	//Set up sprite frames
	for (int i = 0; i < MAX_FRAMES; i++) {
		player->frameRec[i].x = i * (float)player->texture.width / MAX_FRAMES;
		player->frameRec[i].y = 0;
		player->frameRec[i].width = (float)player->texture.width / MAX_FRAMES;
		player->frameRec[i].height = (float)player->texture.height;
	}

	// Initialize other player properties
	player->position = (Vector2){ (float)1920 / 2 + 50, (float)1080 / 2 + 50 };
	player->playerColor = WHITE;
	player->currentFrame = 0;
	player->framesCounter = 0;
	player->framesSpeed = MAX_ANIMATION_SPEED;
}




void DrawSprite(Player *player) {

	DrawTextureRec(player->texture, player->frameRec[player->currentFrame], player->position, player->playerColor);
}