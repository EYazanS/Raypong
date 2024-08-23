#include <raylib.h>

#include "game.h"

int main(void) {
    // Initialization
    Constants constants = {};
    constants.ScreenWidth = 800;
    constants.ScreenHeight = 450;
    constants.Maring = 10;

    GameState game_state = {};

    game_state.Paddless[0].Color = GREEN;
    game_state.Paddless[0].Width = 20;
    game_state.Paddless[0].Height = 60;
    game_state.Paddless[0].Speed = 5;
    game_state.Paddless[0].Location.x = constants.Maring + game_state.Paddless[1].Width;
    game_state.Paddless[0].Location.y = (constants.ScreenHeight / 2) - (game_state.Paddless[0].Height / 2);

    game_state.Paddless[1].Color = GREEN;
    game_state.Paddless[1].Width = 20;
    game_state.Paddless[1].Height = 60;
    game_state.Paddless[1].Speed = 5;
    game_state.Paddless[1].Location.x = constants.ScreenWidth - (constants.Maring + game_state.Paddless[1].Width);
    game_state.Paddless[1].Location.y = (constants.ScreenHeight / 2) - (game_state.Paddless[1].Height / 2);

    game_state.Ball.Color = GREEN;
    game_state.Ball.Speed = 10.0f;
    game_state.Ball.Radius = 20.0f;
    game_state.Ball.Location.x = constants.ScreenWidth / 2;
    game_state.Ball.Location.y = constants.ScreenHeight / 2;
    game_state.Ball.Velocity.x = 1.0f;
    game_state.Ball.Velocity.y = 0.0f;

    InitWindow(constants.ScreenWidth, constants.ScreenHeight, "Snakrray");

    SetTargetFPS(60);

    Vector2 ball_new_location;

    Paddle *player_1 = &game_state.Paddless[0];
    Paddle *player_2 = &game_state.Paddless[1];

    while (!WindowShouldClose()) {
        // Update

        // Player movement
        if (IsKeyDown(KEY_W) && player_1->Location.y > 0) {
            player_1->Location.y -= player_1->Speed;
        }

        if (IsKeyDown(KEY_S) && (player_1->Location.y + (player_1->Height) < constants.ScreenHeight)) {
            player_1->Location.y += player_1->Speed;
        }

        // AI movement
        if (player_2->Location.y > game_state.Ball.Location.y) {
            player_2->Location.y -= player_2->Speed;
        }

        if (player_2->Location.y < game_state.Ball.Location.y) {
            player_2->Location.y += player_2->Speed;
        }

        ball_new_location.x = game_state.Ball.Location.x + (game_state.Ball.Speed * game_state.Ball.Velocity.x);
        ball_new_location.y = game_state.Ball.Location.y + (game_state.Ball.Speed * game_state.Ball.Velocity.y);

        // Player 1 score
        if (ball_new_location.x + game_state.Ball.Radius < 0) {
        }

        // Player 2 score
        if (ball_new_location.x + game_state.Ball.Radius > constants.ScreenWidth) {
        }

        if (ball_new_location.y > constants.ScreenHeight + game_state.Ball.Radius ||
            ball_new_location.y + game_state.Ball.Radius < 0) {
            game_state.Ball.Velocity.y *= -1;
        }

        if (CheckCollisionCircleRec(
                game_state.Ball.Location, game_state.Ball.Radius,
                (Rectangle){player_1->Location.x, player_1->Location.y, (player_1->Location.x + player_1->Width),
                            (player_1->Location.y + player_1->Height)})) {
            game_state.Ball.Velocity.x = 1;
        }

        if (CheckCollisionCircleRec(
                game_state.Ball.Location, game_state.Ball.Radius,
                (Rectangle){player_2->Location.x, player_2->Location.y, (player_2->Location.x + player_2->Width),
                            (player_2->Location.y + player_2->Height)})) {
            game_state.Ball.Velocity.x = -1;
        }

        game_state.Ball.Location.x = ball_new_location.x;
        game_state.Ball.Location.y = ball_new_location.y;

        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawRectangle(0, 0, constants.ScreenWidth, constants.ScreenHeight, DARKGRAY);

        for (int i = 0; i < 2; i++) {
            DrawRectangle(game_state.Paddless[i].Location.x, game_state.Paddless[i].Location.y,
                          game_state.Paddless[i].Width, 60, game_state.Paddless[i].Color);
        }

        DrawCircle(game_state.Ball.Location.x, game_state.Ball.Location.y, game_state.Ball.Radius,
                   game_state.Ball.Color);

        EndDrawing();
    }

    // De-Initialization
    CloseWindow();

    return 0;
}