#ifndef game_h
#define game_h

#include <raylib.h>

typedef struct {
    int Height;
    int Width;
    float Speed;
    Vector2 Position;
    Color Color;
} Paddle;

typedef struct {
    float Radius;
    float Speed;
    Vector2 Position;
    Vector2 Velocity;
    Color Color;
} Ball;

typedef struct {
    Paddle Paddless[2];
    Ball Ball;
    int Player1Score;
    int Player2Score;
    float SleepTimer;
} GameState;

typedef struct {
    int ScreenWidth;
    int ScreenHeight;
    int Margin;
} Constants;

#endif