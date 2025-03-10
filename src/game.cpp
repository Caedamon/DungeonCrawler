#include "game.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include "ui.h"
#include "dungeon.h"
#include "algorithm"

Game::Game() : player(0, 0), dungeonTexture({0}) {
    std::cout << "[DEBUG] Game::Game() started." << std::endl;
    dungeon.LoadTextures();
}

void Game::Init() {
    std::cout << "[DEBUG] Initializing game..." << std::endl;

    // Generate the dungeon first
    dungeon.GenerateDungeon();

    // Now render the dungeon with the player's vision range
    dungeon.RenderToTexture(player);

    std::cout << "[DEBUG] Dungeon generated successfully!" << std::endl;
}

void Game::HandleInput() {
    int dx = 0, dy = 0;

    // Move player with arrow keys or WASD
    if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))  dx = -1;
    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) dx =  1;
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))    dy = -1;
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))  dy =  1;

    // Skip turn
    if (IsKeyPressed(KEY_SPACE)) {
        player.RegenHealth();
        return;
    }

    if (dx != 0 || dy != 0) {
        player.Move(dx, dy, dungeon, monsters);
    }
}

void Game::Update() {
    int dx = 0, dy = 0;

    if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) dx = -1;
    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) dx = 1;
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) dy = -1;
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) dy = 1;

    if (dx != 0 || dy != 0) {
    #if DEBUG_MODE
        std::cout << "[DEBUG] Processing input: dx=" << dx << ", dy=" << dy << std::endl;
    #endif
        player.Move(dx, dy, dungeon, monsters);
    }

    // Monsters attack the player even if they skipped movement
    for (auto& monster : monsters) {
        if (abs(monster.GetX() - player.x) + abs(monster.GetY() - player.y) == 1) {
            monster.AttackPlayer(player);
        }
    }

    // Remove dead monsters from the list
    monsters.erase(
        std::remove_if(monsters.begin(), monsters.end(),
                       [](const Monster& m) { return m.IsDead(); }),
        monsters.end());
}

void Game::Draw() {
    static int lastX = -1, lastY = -1;
    static bool dungeonNeedsRedraw = true;

    // Only redraw the dungeon if the player moves
    if (player.x != lastX || player.y != lastY) {
        #if DEBUG_MODE
        std::cout << "[DEBUG] Player moved to (" << player.x << ", " << player.y << "). Redrawing dungeon." << std::endl;
        #endif

        dungeonNeedsRedraw = true;
        lastX = player.x;
        lastY = player.y;
    }

    if (dungeonNeedsRedraw) {
        dungeon.RenderToTexture(player);
        dungeonNeedsRedraw = false;
    }

    // Draw the cached dungeon texture instead of redrawing everything
    DrawTextureRec(dungeon.dungeonTexture.texture,
                   {0, 0, (float)dungeon.dungeonTexture.texture.width, -(float)dungeon.dungeonTexture.texture.height},
                   {0, 0}, WHITE);
}

void Game::RenderToTexture() {
    std::cout << "[DEBUG] Entering RenderToTexture()" << std::endl;

    // Ensure the window is initialized before rendering
    if (!IsWindowReady()) {
        std::cerr << "[ERROR] RenderToTexture() called before Raylib window initialized!" << std::endl;
        return;
    }

    // Ensure dungeonTexture is valid
    if (dungeonTexture.id == 0) {
        std::cout << "[DEBUG] Initializing dungeonTexture..." << std::endl;
        dungeonTexture = LoadRenderTexture(800, 600);
    }

    BeginTextureMode(dungeonTexture);
    ClearBackground(BLACK);
    dungeon.Draw(player.x, player.y);
    EndTextureMode();

    std::cout << "[DEBUG] Exiting RenderToTexture()" << std::endl;
}

void Game::Run() {
    std::cout << "[DEBUG] Initializing Window..." << std::endl;
    InitWindow(800, 600, "Dungeon Crawler");
    InitAudioDevice();
    SetTargetFPS(60);
    std::cout << "[DEBUG] Window initialized!" << std::endl;

    // Generate the dungeon
    dungeon.GenerateDungeon();
    std::cout << "[DEBUG] Dungeon generated successfully!" << std::endl;

    // Find the stairs and place the player
    bool playerPlaced = false;

    std::cout << "[DEBUG] Dungeon Grid before placing player:\n";
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            std::cout << dungeon.grid[y][x];
        }
        std::cout << std::endl;
    }

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (dungeon.grid[y][x] == '^') {
                player.x = x;
                player.y = y;
                playerPlaced = true;
                std::cout << "[DEBUG] Player placed at (" << player.x << ", " << player.y << ")" << std::endl;
                break;
            }
        }
        if (playerPlaced) break;
    }

    if (!playerPlaced) {
        std::cerr << "[ERROR] Player was not placed! Defaulting to (5,5)." << std::endl;
        player.x = 5;
        player.y = 5;
    }

    std::cout << "[DEBUG] Game setup completed!" << std::endl;

    currentState = GameState::MENU;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        switch (currentState) {
            case GameState::MENU:
                DrawStartScreen(*this);
                break;
            case GameState::HERO_SELECTION:
                DrawHeroSelectionScreen(*this);
                break;
            case GameState::GAME:
                HandleInput();
                Update();
                Draw();
                break;
            case GameState::EXIT:
                CloseWindow();
                return;
        }

        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
    std::cout << "[DEBUG] Exiting game loop..." << std::endl;
}