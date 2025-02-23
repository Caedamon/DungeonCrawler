#include "game.h"
#include "ui.h"
#include "raylib.h"
#include <iostream>

Game::Game() {
    currentState = MENU;  // Start in the menu
}

void Game::Run() {
    InitWindow(800, 600, "Dungeon Adventure");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        HandleInput();
        Update();

        BeginDrawing();
        ClearBackground(BLACK);
        Draw();
        EndDrawing();
    }

    CloseWindow();
}

void Game::HandleInput() {
    if (IsKeyPressed(KEY_ESCAPE)) {
        currentState = EXIT;
    }
}

void Game::Update() {
    if (currentState == MENU) {
        if (DrawButton(250, 250, 300, 50, "Start New Adventure")) {
            currentState = HERO_SELECTION;
        }
        if (DrawButton(250, 320, 300, 50, "Load Adventure")) {
            currentState = LOAD;
        }
        if (DrawButton(250, 390, 300, 50, "Run Away From The Dungeons!")) {
            currentState = EXIT;
        }
    }
    else if (currentState == HERO_SELECTION) {
        if (DrawButton(300, 420, 200, 50, "Start Adventure")) {
            StartNewDungeon();
        }
    }
}

void Game::Draw() {
    if (currentState == MENU) {
        DrawStartScreen((int&)currentState);
    }
    else if (currentState == HERO_SELECTION) {
        DrawHeroSelectionScreen((int&)currentState);
    }
    else if (currentState == GAME) {
        currentDungeon.Draw();
    }
    else if (currentState == EXIT) {
        DrawText("Exiting Game...", 300, 300, 30, RED);
    }
}

void Game::StartNewDungeon() {
    currentState = GAME;
    currentDungeon = Dungeon();
    currentDungeon.RenderToTexture();
    std::cout << "New dungeon generated." << std::endl;
}