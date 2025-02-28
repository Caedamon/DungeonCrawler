#include "game.h"
#include <iostream>
#include <filesystem>
#include <fstream>

Game::Game() : player(0, 0) {  // Initialize player
    dungeon.GenerateDungeon();

    // Place player at the stairs (^)
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (dungeon.grid[y][x] == "^") {
                player.x = x;
                player.y = y;
                return;
            }
        }
    }
}

void Game::HandleInput() {
    int dx = 0, dy = 0;

    if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))  dx = -1;
    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) dx =  1;
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))    dy = -1;
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))  dy =  1;

    if (IsKeyPressed(KEY_SPACE)) {  // Skip turn
        player.RegenHealth();
        return;
    }

    if (dx != 0 || dy != 0) {
        player.Move(dx, dy, dungeon, monsters);
    }
}

void Game::Update() {
    HandleInput();
}

void Game::Draw() {
    dungeon.Draw();

    // Draw player using ASCII symbol "¤"
    DrawText("¤", player.x * 20, player.y * 20, 20, BLUE);
}

void Game::Run() {
    // Initialize Raylib Window
    InitWindow(800, 600, "Dungeon Crawler");
    InitAudioDevice(); // For sound support
    SetTargetFPS(60);

    std::cout << "Current Working Directory: " << std::filesystem::current_path() << std::endl;

    // Main Game Loop
    while (!WindowShouldClose()) {
        Update();
        BeginDrawing();
        ClearBackground(BLACK);
        Draw();
        EndDrawing();
    }

    // Properly Close Everything
    CloseAudioDevice();
    CloseWindow();
}
