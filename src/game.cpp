#include "game.h"
#include <iostream>
#include <filesystem>
#include <fstream>

#include "ui.h"

Game::Game() : player(0, 0), dungeonTexture({0}) {
    std::cout << "[DEBUG] Game::Game() started." << std::endl;
    dungeon.GenerateDungeon();
    std::cout << "[DEBUG] dungeon.GenerateDungeon() finished." << std::endl;

    // Find the stairs in the dungeon and place the player there
    bool playerPlaced = false;

    // Debugging: Print the dungeon grid before searching for stairs
    std::cout << "[DEBUG] Dungeon Grid before placing player:\n";
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            std::cout << dungeon.grid[y][x];
        }
        std::cout << std::endl;
    }

    // Search for stairs
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (dungeon.grid[y][x] == "^") {
                player.x = x;
                player.y = y;
                playerPlaced = true;
                std::cout << "[DEBUG] Player placed at (" << player.x << ", " << player.y << ")" << std::endl;
                break;
            }
        }
        if (playerPlaced) break;
    }

    // If no stairs were found, log the error
    if (!playerPlaced) {
        std::cerr << "[ERROR] Player was not placed! Defaulting to (5,5)." << std::endl;
        player.x = 5;
        player.y = 5;
    }

    std::cout << "[DEBUG] Game::Game() finished." << std::endl;
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
    static int lastX = player.x, lastY = player.y;

    // Update player position
    if (IsKeyPressed(KEY_RIGHT)) player.x++;
    if (IsKeyPressed(KEY_LEFT)) player.x--;
    if (IsKeyPressed(KEY_DOWN)) player.y++;
    if (IsKeyPressed(KEY_UP)) player.y--;

    // Only print debug messages when position changes
    if (player.x != lastX || player.y != lastY) {
        std::cout << "[DEBUG] Player moved to (" << player.x << ", " << player.y << ")" << std::endl;
        lastX = player.x;
        lastY = player.y;
    }
}

void Game::Draw() {
    static int lastX = -1, lastY = -1;

    // Only print debug messages when necessary
    if (player.x != lastX || player.y != lastY) {
        std::cout << "[DEBUG] Drawing dungeon..." << std::endl;
        std::cout << "[DEBUG] Drawing player at (" << player.x << ", " << player.y << ")" << std::endl;
        lastX = player.x;
        lastY = player.y;
    }

    dungeon.Draw(player.x, player.y);
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

    // Generate the dungeon AFTER window is initialized
    std::cout << "[DEBUG] Generating Dungeon after initializing window..." << std::endl;
    dungeon.GenerateDungeon();
    std::cout << "[DEBUG] Dungeon generated successfully!" << std::endl;

    // Call RenderToTexture AFTER initializing the window
    std::cout << "[DEBUG] Calling RenderToTexture()..." << std::endl;
    RenderToTexture();
    std::cout << "[DEBUG] RenderToTexture() completed!" << std::endl;

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
                Update();
            Draw();
            break;
            case GameState::EXIT:
                CloseWindow();
            return;
            default:
                break;
        }

        EndDrawing();
    }

    std::cout << "[DEBUG] Exiting game loop..." << std::endl;
    CloseAudioDevice();
    CloseWindow();
}