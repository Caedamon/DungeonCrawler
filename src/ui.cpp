#include "ui.h"
#include "button.h"
#include "dungeon.h"
#include "game.h"
#include "raylib.h"
#include <iostream>

void DrawStartScreen(Game &game) {
    DrawText("Welcome Adventurer! To the Dungeon Adventure!", 120, 100, 24, WHITE);

    if (DrawButton(250, 250, 300, 50, "Start Adventure")) {
        std::cout << "[DEBUG] Start button clicked!" << std::endl;
        game.currentState = GameState::HERO_SELECTION;
    }

    if (DrawButton(250, 320, 300, 50, "Load Adventure")) {
        std::cout << "[DEBUG] Load button clicked!" << std::endl;
        game.currentState = GameState::LOAD;
    }

    if (DrawButton(250, 390, 300, 50, "Quit")) {
        std::cout << "[DEBUG] Quit button clicked!" << std::endl;
        game.currentState = GameState::EXIT;
    }
}

void DrawHeroSelectionScreen(Game &game) {
    DrawText("Pick Your Hero", 300, 100, 30, WHITE);
    DrawText("Adventurer", 350, 160, 24, YELLOW);

    DrawText("Equipment:", 300, 200, 20, WHITE);
    DrawText("- Sword", 320, 230, 18, LIGHTGRAY);
    DrawText("- Shield", 320, 260, 18, LIGHTGRAY);

    DrawText("Skills:", 300, 300, 20, WHITE);
    DrawText("- Find Trap", 320, 330, 18, LIGHTGRAY);
    DrawText("- Pick Lock", 320, 360, 18, LIGHTGRAY);

    if (DrawButton(300, 420, 200, 50, "Start Adventure")) {
        std::cout << "[DEBUG] Player has selected their hero! Starting the adventure..." << std::endl;
        game.currentState = GameState::GAME;
    }
}