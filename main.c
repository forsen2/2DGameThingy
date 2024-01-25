#include "include/raylib.h"
#include "include/sprite.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>


const int screenWidth = 1920;
const int screenHeight = 1080;

bool quitMoveObstacle = false;
bool gameOver = false;

Camera2D camera = { 0 };
Player player, polygon;

float calculateDistance(float playerX, float playerY, float enemyX, float enemyY)
{
    return sqrt(((playerX - enemyX) * (playerX - enemyX)) + ((playerY - enemyY) * (playerY - enemyY)));
}

void keyControl()
{
    if (IsKeyDown(KEY_D) && gameOver == false)
    {
        player.position.x += 8.0f;
        player.currentFrame = 1;
        player.frameRec.y = player.currentFrame * player.frameRec.height + 3;
        
        
        const int counterFixed = 50;
        static int counterSumming = 0;  

     
        if (player.frameRec.x >= 289) {
            player.frameRec.x = 0;
      
        }
        else if (counterSumming >= counterFixed) {
            counterSumming = 0;
        }
        else{
            player.frameRec.x = player.currentFrame * player.frameRec.width;
            player.frameRec.x += 50;
            if (counterSumming > 10) {
                player.frameRec.x += 100;
                if (counterSumming > 30) {
                    player.frameRec.x += 50;
                }
            }
            counterSumming++;
        
        }


       
        
    }

    if (IsKeyDown(KEY_A) && gameOver == false)
    {
        player.position.x -= 8.0f;
       
    }
    if (IsKeyDown(KEY_W) && gameOver == false)
    {
        player.position.y -= 8.0f;
        
    }
    if (IsKeyDown(KEY_S) && gameOver == false)
    {
        player.position.y += 8.0f;
      
    }
}

void moveObstacle()
{
    if (!quitMoveObstacle)
    {
        if (polygon.position.x != player.position.x && polygon.position.y != player.position.y)
        {
            float CalculatedDist = calculateDistance(player.position.x, player.position.y, polygon.position.x, polygon.position.y);
            if (CalculatedDist > 0.0f)
            {
                float directionX = (player.position.x - polygon.position.x) / CalculatedDist;
                float directionY = (player.position.y - polygon.position.y) / CalculatedDist;
                polygon.position.x += directionX * 5;
                polygon.position.y += directionY * 5;
            }
        }
    }
}

void resetGame()
{
    if (IsKeyDown(KEY_ENTER))
    {
        gameOver = false;
        quitMoveObstacle = false;
        player.position.x = (float)screenWidth / 2 + 50;
        player.position.y = (float)screenWidth / 2 + 50;

        polygon.position.x = (float)screenWidth / 2;
        polygon.position.y = (float)screenHeight / 2;

        keyControl();
        moveObstacle();
    }
}

void setCamera()
{
    camera.target = (Vector2){ player.position.x, player.position.y };
    camera.offset = (Vector2){ screenWidth / 2.0f, screenHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}

void UpdateGame()
{
    bool collision = false;
    keyControl();
    camera.target = (Vector2){ player.position.x + 20.0f, player.position.y + 20.0f };
    moveObstacle();

    // check for collision
    if (CheckCollisionBoxes(
        (BoundingBox) { {player.position.x - 10, player.position.y - 10, -10},
        { player.position.x + 10, player.position.y + 10, 10 }
    },
        (BoundingBox) { {polygon.position.x - 20, polygon.position.y - 20, -20},
        { polygon.position.x + 20, polygon.position.y + 20, 20 }
    }))
    {
        collision = true;
    }
    else
    {
        collision = false;
    }

    if (collision)
    {
        player.playerColor = GREEN;
        quitMoveObstacle = true;
        gameOver = true;
        DrawText("GAME OVER! YOU TOUCHED THE POLYGON! TO PLAY AGAIN PRESS ENTER", 10, 50, 20, LIGHTGRAY);
        resetGame();
    }
    else
    {
        player.playerColor = RED;
    }
}

Texture2D loadMapTexture()
{
    const char* filename = "C:/Users/olihb/Desktop/projects/2DCycleGame/textures/level1/grass00.png";
    Image image = LoadImage(filename);
    Texture2D mapTexture = LoadTextureFromImage(image);
    UnloadImage(image);
    return mapTexture;
}

void initPlayerPos() {
    player.position.x = (float)screenWidth / 2 + 50;
    player.position.y = (float)screenHeight / 2 + 50;

}

void initPolygonPos() {
    polygon.position.x = (float)screenWidth / 2;
    polygon.position.y = (float)screenHeight / 2;
    

}

int main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "game");

    Texture2D mapTexture = loadMapTexture();
    Texture2D spriteSheet = loadPlayerSpriteSheet(&player);

    initPlayerPos();
    initSpriteConfig(&player, &spriteSheet);
    initSpriteConfig(&player, &spriteSheet);


    setCamera();
    SetTargetFPS(60);
    float rotation = 0.0f;

    while (!WindowShouldClose())
    {
        player.framesCounter++;

        addSpriteWatcher(&player);
        UpdateGame();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode2D(camera);

        DrawTextureRec(mapTexture, (Rectangle) { player.position.x - camera.offset.x, player.position.y - camera.offset.y, screenWidth, screenHeight }, (Vector2) { (player.position.x - camera.offset.x + 20), (player.position.y - camera.offset.y + 20) }, WHITE);
        
        // Adjust the sprite frame based on the movement direction use this up on the movements part 

        DrawTextureRec(spriteSheet, player.frameRec, (Vector2) { player.position.x - player.frameRec.width / 2 - (spriteSheet.width / 8) + 25, player.position.y - player.frameRec.height / 2 }, WHITE);



        DrawCircleV(player.position, 10, player.playerColor);
        DrawPoly(polygon.position, 6, 20, rotation, BROWN);

        EndMode2D();
        EndDrawing();
    }

    UnloadTexture(mapTexture);
    UnloadTexture(spriteSheet);
    CloseWindow();

    return 0;
}
