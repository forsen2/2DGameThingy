
#include "include/raylib.h"
#define KEY_W 87
#define KEY_A 65
#define KEY_D 68
#define KEY_S 83
#define KEY_RESET 08
const int screenWidth = 1200;
const int screenHeight = 1200;

bool quitMoveObstacle = false;
bool gameOver = false;


Camera2D camera = { 0 };
Color playerColor;

typedef struct {
    Vector2 position;
    Color playerColor;

} Player; Player player, polygon;


void keyControl() {

        if (IsKeyDown(KEY_D) && gameOver == false) player.position.x += 8.0f; 
        if (IsKeyDown(KEY_A) && gameOver == false) player.position.x -= 8.0f;
        if (IsKeyDown(KEY_W) && gameOver == false) player.position.y -= 8.0f;
        if (IsKeyDown(KEY_S) && gameOver == false) player.position.y += 8.0f;

}

void moveObstacle() {
    
    if (!quitMoveObstacle) {
        static int direction = 1;
        if (polygon.position.y > 45.0f && direction == 1) {
            polygon.position.y -= 5.0f;
            if (polygon.position.y <= 45.0f) {
                direction = -1;
            }
        }
        else if (polygon.position.y <= screenHeight - 45.0f && direction == -1) {
            polygon.position.y += 5.0f;
            if (polygon.position.y >= screenHeight - 45.0f) {
                direction = 1;
            }
        }
    }
}


void resetGame() {
    if (IsKeyDown(KEY_ENTER)) {
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

void setCamera() {
    camera.target = (Vector2){ player.position.x + 20.0f, player.position.y + 20.0f };
    camera.offset = (Vector2){ screenWidth / 2.0f, screenHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}


void UpdateGame() {
    bool collision = false;
    keyControl();
    camera.target = (Vector2){ player.position.x + 20.0f, player.position.y + 20.0f };
    moveObstacle();


    // Check for collision
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


    if (collision) {
        playerColor = GREEN;
        quitMoveObstacle = true;
        gameOver = true;
        DrawText("GAME OVER! YOU TOUCHED THE POLYGON! TO PLAY AGAIN PRESS ENTER", 10, 50, 20, LIGHTGRAY);
        resetGame();
    }
    else {
        playerColor = RED;
    }
}

int main(void)
{

    //Initialization-----------------------------------------------------------------------
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "game");
    const char *filename = "C:/Users/olihb/Desktop/projects/2DCycleGame/textures/level1/grass00.png";

    Image image = LoadImage(filename);      
    Texture2D cubicmap = LoadTextureFromImage(image);   

    UnloadImage(image);
    //-------------------------------------------------------------------------------------

   //variables
    player.position.x = (float)screenWidth / 2 + 50;
    player.position.y = (float)screenHeight / 2 + 50;
    polygon.position.x = (float)screenWidth / 2;
    polygon.position.y = (float)screenHeight / 2;
    float rotation = 0.0f;
    //-------------------------------------------------------------------------------------
    setCamera();
    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        rotation += 2.0f;

        UpdateGame();
        BeginDrawing();
            ClearBackground(RAYWHITE);   
            BeginMode2D(camera);

            DrawTextureEx(cubicmap, (Vector2) { screenWidth - cubicmap.width * 4.0f - 20, 20.0f }, 0.0f, 4.0f, WHITE);
            DrawCircleV(player.position, 10, playerColor);
            DrawPoly(polygon.position, 6, 20, rotation, BROWN);
            
            EndMode2D();
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(cubicmap);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}