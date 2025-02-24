#include "ui.h"
#include "button.h"
#include "dungeon.h"
#include "game.h"
#include "raylib.h"
#include <iostream>

void DrawStartScreen(Game &game) {
    DrawText("Welcome Adventurer! To the Dungeon Adventure!", 120, 100, 24, WHITE);

    if (DrawButton(250, 250, 300, 50, "Start New Adventure")) {
        game.currentState = HERO_SELECTION; // Move to Hero Selection
    }

    if (DrawButton(250, 320, 300, 50, "Load Adventure")) {
        game.currentState = LOAD;   // Load Game
    }

    if (DrawButton(250, 390, 300, 50, "Run Away From The Dungeons!")) {
        CloseWindow();  // Properly closes Raylib
        exit(0);
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
        std::cout << "Start Adventure clicked! Switching to GAME..." << std::endl;
        game.currentState = GAME;  // Move to the game screen (i hope...)
    }
}

bool DrawButton(int x, int y, int width, int height, const char *text) {
    Rectangle buttonBounds = { static_cast<float>(x), static_cast<float>(y),
                           static_cast<float>(width), static_cast<float>(height) };
    bool isHovered = CheckCollisionPointRec(GetMousePosition(), buttonBounds);

    Color buttonColor = isHovered ? DARKGRAY : LIGHTGRAY;
    DrawRectangleRec(buttonBounds, buttonColor);

    int textWidth = MeasureText(text, 20);
    DrawText(text, x + (width - textWidth) / 2, y + (height - 20) / 2, 20, BLACK);

    return isHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}