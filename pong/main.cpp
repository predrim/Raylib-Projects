#include <iostream>
#include "raylib.h"


int main(void)
{
    // Initialization
    const int screenWidth = 1200;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Pong");

    SetTargetFPS(60);


    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update

        // Draw
        BeginDrawing();

            ClearBackground(BLACK);

            // Ball
            DrawCircle(screenWidth/2, screenHeight/2, 20.0, WHITE);
            
            // Left Paddle
            DrawRectangle(15, screenHeight/2-60, 25, 120, WHITE);
            
            // Right Paddle
            DrawRectangle(screenWidth-40, screenHeight/2-60, 25, 120, WHITE);

            // Center Line
            DrawLine(screenWidth/2, 0, screenWidth/2, screenHeight, WHITE);

        EndDrawing();
    }

    // De-Initialization

    CloseWindow();
  
    return 0;
}