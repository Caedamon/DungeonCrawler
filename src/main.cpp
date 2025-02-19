#include "raylib.h"
#include "ui.h"
#include "dungeon.h"
#include "game_state.h"
#include <iostream>

GameState currentScreen = MENU;
Dungeon currentDungeon;
bool dungeonGenerated = false;  // Prevent regenerating every frame

void StartNewFloor() {
    currentDungeon = Dungeon();  // Generate dungeon only once per floor
    dungeonGenerated = true;
    std::cout << "Generated a new dungeon." << std::endl;
}

int main() {
    InitWindow(800, 600, "Dungeon Adventure");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        if (currentScreen == MENU) {
            DrawStartScreen((int&)currentScreen);
        }
        else if (currentScreen == HERO_SELECTION) {
            DrawHeroSelectionScreen((int&)currentScreen);
        }
        else if (currentScreen == GAME) {
            if (!dungeonGenerated) {
                StartNewFloor();  // Only generate once
            }
            currentDungeon.Draw();  // Actually draw the dungeon
        }

        EndDrawing();

        if (currentScreen == EXIT) {
            break;
        }
    }

    CloseWindow();
    return 0;
}
