#include "raylib.h"
#include "ui.h"

enum GameState { MENU, HERO_SELECTION, LOAD_GAME, EXIT_GAME };
GameState currentScreen = MENU;

int main() {
    InitWindow(800, 600, "Dungeon Adventure");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        if (currentScreen == MENU) {
            DrawStartScreen((int&)currentScreen);
        }
        else if (currentScreen == HERO_SELECTION) {
            DrawHeroSelectionScreen((int&)currentScreen);
        }
        else if (currentScreen == LOAD_GAME) {
            DrawText("Loading Adventure...", 250, 280, 20, WHITE);
        }

        EndDrawing();

        if (currentScreen == EXIT_GAME) {
            break;
        }
    }

    CloseWindow();
    return 0;
}
