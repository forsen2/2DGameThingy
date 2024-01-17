
#include "include/raylib.h"
#define KEY_W 87
#define KEY_A 65
#define KEY_D 68
#define KEY_S 83
#define KEY_RESET 08
const int screenWidth = 800;
const int screenHeight = 450;
static bool quitMoveObstacle = false;
bool gameOver = false;
Vector2 ballPosition;
Vector2 polygonPosition;


void keyControl() {

        if (IsKeyDown(KEY_D) && gameOver == false) ballPosition.x += 8.0f; 
        if (IsKeyDown(KEY_A) && gameOver == false) ballPosition.x -= 8.0f;
        if (IsKeyDown(KEY_W) && gameOver == false) ballPosition.y -= 8.0f;
        if (IsKeyDown(KEY_S) && gameOver == false) ballPosition.y += 8.0f;
 


}

void moveObstacle() {
    
    if (!quitMoveObstacle) {
        static int direction = 1;
        if (polygonPosition.y > 45.0f && direction == 1) {
            polygonPosition.y -= 5.0f;
            if (polygonPosition.y <= 45.0f) {
                direction = -1;
            }
        }
        else if (polygonPosition.y <= screenHeight - 45.0f && direction == -1) {
            polygonPosition.y += 5.0f;
            if (polygonPosition.y >= screenHeight - 45.0f) {
                direction = 1;
            }
        }
    }
}


void resetGame() {
    if (IsKeyDown(KEY_ENTER)) {
        gameOver = false;
        quitMoveObstacle = false;
        ballPosition.x = (float)screenWidth / 2 + 50;
        ballPosition.y = (float)screenWidth / 2 + 50;


        polygonPosition.x = (float)screenWidth / 2;
        polygonPosition.y = (float)screenHeight / 2;
        
        keyControl();
        moveObstacle();

        
    }
}


int main(void)
{
    bool collision = false;
    //Initialization-----------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "game");
    //-------------------------------------------------------------------------------------

   //variables
    ballPosition.x = (float)screenWidth / 2 + 50;
    ballPosition.y = (float)screenHeight / 2 + 50;

    polygonPosition.x = (float)screenWidth / 2;
    polygonPosition.y = (float)screenHeight / 2;

    float rotation = 0.0f;
  
    Color playerColor = RED;

    //------
    SetTargetFPS(60);               
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        rotation += 2.0f;
        keyControl();
        moveObstacle();


        // Check for collision
        if (CheckCollisionBoxes(
            (BoundingBox) { {ballPosition.x - 10, ballPosition.y - 10, -10},
            { ballPosition.x + 10, ballPosition.y + 10, 10 }
        },
            (BoundingBox) { {polygonPosition.x - 20, polygonPosition.y - 20, -20},
            { polygonPosition.x + 20, polygonPosition.y + 20, 20 }
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
        

        BeginDrawing();

        ClearBackground(BLACK);
        DrawCircleV(ballPosition, 10, playerColor);
        DrawPoly(polygonPosition, 6, 20, rotation, BROWN);
        

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}