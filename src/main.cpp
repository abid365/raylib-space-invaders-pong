#include <iostream>
#include <raylib.h>
using namespace std;

int human_player_score = 0;
int pc_player_score = 0;

class Ball
{

public:
    float x, y;
    int speed_X, speed_Y;
    int radius;
    Texture2D ballTexture;
    float scale;

    void DrawSprite()
    {
        // DrawCircle(x, y, radius, WHITE);
        // DrawTexture(ballTexture, x - ballTexture.width / 2, y - ballTexture.height / 2, WHITE);
        DrawTextureEx(ballTexture, {x - (ballTexture.width * scale) / 2, y - (ballTexture.height * scale) / 2}, 0.0f, scale, WHITE);
    };
    void MoveSpire()
    {
        x += speed_X;
        y += speed_Y;
        if (y + radius >= GetScreenHeight() || y - radius <= 0)
        {
            speed_Y *= -1;
        };
        if (x + radius >= GetScreenWidth())

        {
            pc_player_score++;
            speed_X *= -1;
        }
        if (x - radius <= 0)
        {
            human_player_score++;
            speed_X *= -1;
        }
    }
};

class Stamp
{
protected:
    void RestrictMoveMent()
    {
        if (y <= 0)
        {
            y = 0;
        }
        if (y + height >= GetScreenHeight())
        {
            y = GetScreenHeight() - height;
        }
    };

public:
    float x, y;
    float width, height;
    int speed;

    void DrawStamp()
    {
        DrawRectangle(x, y, width, height, WHITE);
    }

    void MoveStamp()
    {
        if (IsKeyDown(KEY_UP))
        {
            y = y - speed;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            y = y + speed;
        }

        RestrictMoveMent();
    };
};

class StampTwo : public Stamp
{
public:
    // void MoveStamp(int ball_at_y_axis)
    // {
    //     if (y + height / 2 >= ball_at_y_axis)
    //     {
    //         y = y - speed;
    //     }
    //     if (y + height / 2 <= ball_at_y_axis)
    //     {
    //         y = y + speed;
    //     }

    //     RestrictMoveMent();
    // }

    void MoveStamp()
    {
        if (IsKeyDown(KEY_W))
        {
            y = y - speed;
        }
        if (IsKeyDown(KEY_S))
        {
            y = y + speed;
        }

        RestrictMoveMent();
    };
};

Ball ball;
Stamp humanPlayer;
StampTwo pcPlayer;

int main()
{
    cout << "Starting the game" << endl;
    const int screenHeight = 800;
    const int screenWidth = 1280;
    SetTargetFPS(60);
    // ball.radius = 20;
    ball.scale = 0.08f;
    ball.radius = (ball.ballTexture.width * ball.scale) / 2;
    ball.x = screenWidth / 2;
    ball.y = screenHeight / 2;
    ball.speed_X = 5;
    ball.speed_Y = 5;

    humanPlayer.width = 25;
    humanPlayer.height = 120;
    humanPlayer.x = screenWidth - humanPlayer.width - 10;
    humanPlayer.y = screenHeight / 2 - humanPlayer.height / 2;
    humanPlayer.speed = 6;

    pcPlayer.width = 25;
    pcPlayer.height = 120;
    pcPlayer.x = 10;
    pcPlayer.y = screenHeight / 2;
    pcPlayer.speed = 8;

    InitWindow(screenWidth, screenHeight, "Space Invaders");
    ball.ballTexture = LoadTexture("venus.png");
    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ball.MoveSpire();
        humanPlayer.MoveStamp();
        pcPlayer.MoveStamp();

        // collision detection , for example the below logic will check if the ball is collided with the stamp or not.
        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, {humanPlayer.x, humanPlayer.y, humanPlayer.width, humanPlayer.height}))
        {
            ball.speed_X *= -1;
        }

        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, {pcPlayer.x, pcPlayer.y, pcPlayer.width, pcPlayer.height}))
        {
            ball.speed_X *= -1;
        }

        ClearBackground(BLACK);
        DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
        ball.DrawSprite();
        humanPlayer.DrawStamp();
        pcPlayer.DrawStamp();
        DrawText(TextFormat("%i", pc_player_score), screenWidth / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", human_player_score), 3 * screenWidth / 4 - 20, 20, 80, WHITE);
        EndDrawing();
    };
    UnloadTexture(ball.ballTexture);
    CloseWindow();

    return 0;
}