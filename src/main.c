#include <raylib.h>

#include "game.h"

void reset_game(Constants constants, GameState *game_state) {
    game_state->Paddless[0].Color = GREEN;
    game_state->Paddless[0].Width = 20;
    game_state->Paddless[0].Height = 60;
    game_state->Paddless[0].Speed = 10;
    game_state->Paddless[0].Position.x = constants.Margin + game_state->Paddless[1].Width;
    game_state->Paddless[0].Position.y = (constants.ScreenHeight / 2) - (game_state->Paddless[0].Height / 2);

    game_state->Paddless[1].Color = GREEN;
    game_state->Paddless[1].Width = 20;
    game_state->Paddless[1].Height = 60;
    game_state->Paddless[1].Speed = 10;
    game_state->Paddless[1].Position.x = constants.ScreenWidth - (constants.Margin + game_state->Paddless[1].Width);
    game_state->Paddless[1].Position.y = (constants.ScreenHeight / 2) - (game_state->Paddless[1].Height / 2);

    float x_velocity = (int)GetRandomValue(0, 1) ? 1.0f : -1.0f;
    float y_velocity = (int)GetRandomValue(0, 1) ? 1.0f : -1.0f;

    game_state->Ball.Color = GREEN;
    game_state->Ball.Speed = 5.0f;
    game_state->Ball.Radius = 20.0f;
    game_state->Ball.Position.x = constants.ScreenWidth / 2;
    game_state->Ball.Position.y = constants.ScreenHeight / 2;
    game_state->Ball.Velocity.x = x_velocity;
    game_state->Ball.Velocity.y = y_velocity;

    game_state->SleepTimer = 1000;
}

int main(void) {
    // Initialization
    Constants constants = {};

    constants.ScreenWidth = 800;
    constants.ScreenHeight = 450;
    constants.Margin = 10;

    GameState game_state = {};

    reset_game(constants, &game_state);

    InitWindow(constants.ScreenWidth, constants.ScreenHeight, "Raypong");

    SetTargetFPS(60);

    Paddle *player_1 = &game_state.Paddless[0];
    Paddle *player_2 = &game_state.Paddless[1];

    while (!WindowShouldClose()) {
        // Update
        if (game_state.SleepTimer <= 0) {
            // Player movement
            if (IsKeyDown(KEY_W) && player_1->Position.y > 0) {
                player_1->Position.y -= player_1->Speed;
            }

            if (IsKeyDown(KEY_S) && (player_1->Position.y + (player_1->Height) < constants.ScreenHeight)) {
                player_1->Position.y += player_1->Speed;
            }

            // AI movement
            if (player_2->Position.y > game_state.Ball.Position.y) {
                player_2->Position.y -= player_2->Speed;
            }

            if (player_2->Position.y < game_state.Ball.Position.y) {
                player_2->Position.y += player_2->Speed;
            }

            Rectangle player_1_rect = {player_1->Position.x, player_1->Position.y, player_1->Width, player_1->Height};
            Rectangle player_2_rect = {player_2->Position.x, player_2->Position.y, player_2->Width, player_2->Height};

            game_state.Ball.Position.x =
                game_state.Ball.Position.x + (game_state.Ball.Speed * game_state.Ball.Velocity.x);
            game_state.Ball.Position.y =
                game_state.Ball.Position.y + (game_state.Ball.Speed * game_state.Ball.Velocity.y);

            if (game_state.Ball.Position.y > constants.ScreenHeight + game_state.Ball.Radius ||
                game_state.Ball.Position.y + game_state.Ball.Radius < 0) {
                game_state.Ball.Velocity.y *= -1;
            }

            if (CheckCollisionCircleRec(game_state.Ball.Position, game_state.Ball.Radius, player_1_rect)) {
                game_state.Ball.Velocity.x = 1;
                game_state.Ball.Speed += 0.4;
            }

            if (CheckCollisionCircleRec(game_state.Ball.Position, game_state.Ball.Radius, player_2_rect)) {
                game_state.Ball.Velocity.x = -1;
                game_state.Ball.Speed += 0.4f;
            }

            // Player 1 score
            if (game_state.Ball.Position.x + game_state.Ball.Radius < 0) {
                game_state.Player2Score++;
                reset_game(constants, &game_state);
            }

            // Player 2 score
            if (game_state.Ball.Position.x + game_state.Ball.Radius > constants.ScreenWidth) {
                game_state.Player1Score++;
                reset_game(constants, &game_state);
            }
        }

        game_state.SleepTimer -= (GetFrameTime() * 1000);

        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawRectangle(0, 0, constants.ScreenWidth, constants.ScreenHeight, DARKGRAY);

        for (int i = 0; i < 2; i++) {
            DrawRectangle(game_state.Paddless[i].Position.x, game_state.Paddless[i].Position.y,
                          game_state.Paddless[i].Width, 60, game_state.Paddless[i].Color);
        }

        DrawCircle(game_state.Ball.Position.x, game_state.Ball.Position.y, game_state.Ball.Radius,
                   game_state.Ball.Color);

        DrawText(TextFormat("Player 1: %i", game_state.Player1Score), (constants.ScreenWidth / 5), constants.Margin * 2,
                 24, GREEN);
        DrawText(TextFormat("Player 2: %i", game_state.Player2Score), (constants.ScreenWidth / 5) * 3,
                 constants.Margin * 2, 24, GREEN);

        EndDrawing();
    }

    // De-Initialization
    CloseWindow();

    return 0;
}