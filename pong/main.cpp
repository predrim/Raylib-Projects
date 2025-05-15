#include <iostream>
#include <raylib.h>

int playerScore{};
int opponentScore{};
Color green = Color{38, 185, 154, 255};
Color darkGreen = Color{20, 160, 133, 255};
Color lightGreen = Color{129, 204, 184, 255};
Color yellow = Color{243, 213, 91, 255};

class Ball 
{
    public:
    float posX{}, posY{};
    int speedX{}, speedY{};
    double radius{};
    Color color{};

    void Draw() {
        DrawCircle(posX, posY, radius, color);
    }

    void UpdatePos() {
        posX += speedX; 
        posY += speedY; 

        if(posY + radius >= GetScreenHeight() || posY - radius <= 0)
        {
            speedY *= -1; 
        }

        if(posX + radius >= GetScreenWidth()) // Cpu/Opponent wins
        {
            opponentScore++;
            ResetBall();
        }
        if(posX - radius <= 0) 
        {
            playerScore++;
            ResetBall(); 
        }
        
    } 

    void ResetBall()
    {
        posX = GetScreenWidth()/2;
        posY = GetScreenHeight()/2;

        int speedChoices[2] = {-1, 1};
        speedX *= speedChoices[GetRandomValue(0,1)];
        speedY *= speedChoices[GetRandomValue(0,1)];
    }
};

class Paddle
{
    protected:
    void LimitMovement(){
        // Prevents the paddle from going out of the screen.
        if(posY <= 0) {
            posY = 0;
        }
        if(posY + height >= GetScreenHeight()) {
            posY = GetScreenHeight() - height;
        }
    }

    public:
    float posX{}, posY{};
    float width{}, height{};
    float move{};
    Color color;

    void Draw() {
        DrawRectangleRounded(Rectangle{posX, posY, width, height}, 0.8, 0, color);
    }

    void UpdatePos() {
        if (IsKeyDown(KEY_DOWN)) {
            posY += move;
        }
        if (IsKeyDown(KEY_UP)) {
            posY -= move;
        }
        
        LimitMovement();
    }

};

class CpuPaddle: public Paddle
{
    public:
        void UpdatePos(int ballY){
            if(posY + height/2 > ballY){
                posY -= move;
            }
            if(posY + height/2 < ballY){
                posY += move;
            }
            LimitMovement();
        }
};


int main(void)
{
    // Initialization
    const int screenWidth = 1200;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Pong");
    SetTargetFPS(60);

    // Initialize Ball
    Ball ball;
    ball.posX = screenWidth/2;
    ball.posY = screenHeight/2;
    ball.radius = 20.0;
    ball.color = yellow;
    ball.speedX = 7;
    ball.speedY = 7;

    // Initialize Player Paddle
    Paddle player;
    player.width = 25;
    player.height = 120; 
    player.posX = screenWidth-35;
    player.posY = screenHeight/2 - player.height/2;
    player.move = 7;
    player.color = WHITE;

    // Initialize Cpu Paddle
    CpuPaddle opponent;
    opponent.width = 25;
    opponent.height = 120;
    opponent.posX = 10;
    opponent.posY = screenHeight/2 - opponent.height/2;
    opponent.move = 5.5;
    opponent.color = WHITE;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        ball.UpdatePos();
        player.UpdatePos();
        opponent.UpdatePos(ball.posY);

        //Checking for collisions
        if(CheckCollisionCircleRec(Vector2{ball.posX, ball.posY}, ball.radius, Rectangle{player.posX, player.posY, player.width, player.height}))
        {
            ball.speedX *= -1;
        }
        if(CheckCollisionCircleRec(Vector2{ball.posX, ball.posY}, ball.radius, Rectangle{opponent.posX, opponent.posY, opponent.width, opponent.height}))
        {
            ball.speedX *= -1;
        }

        // Draw
        BeginDrawing();
            ClearBackground(darkGreen);
            DrawRectangle(screenWidth/2, 0, screenWidth/2, screenHeight, green);
            DrawCircle(screenWidth/2,screenHeight/2, 150, lightGreen);
            DrawLine(screenWidth/2, 0, screenWidth/2, screenHeight, WHITE);
            player.Draw();
            opponent.Draw();
            ball.Draw();
            DrawText(TextFormat("%i",opponentScore), screenWidth/4 - 20, 20, 80, WHITE);
            DrawText(TextFormat("%i",playerScore), 3 * screenWidth/4 - 20, 20, 80, WHITE);
        EndDrawing();
    }

    // De-Initialization

    CloseWindow();
  
    return 0;
}