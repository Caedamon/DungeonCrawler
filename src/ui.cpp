#include "ui.h"
#include "button.h"
#include "raylib.h"
#include <iostream>

void DrawStartScreen(int &currentScreen) {
    DrawText("Welcome Adventurer! To the Dungeon Adventure!", 120, 100, 24, WHITE);

    if (DrawButton(250, 250, 300, 50, "Start New Adventure")) {
        currentScreen = HERO_SELECTION;// Move to Hero Selection
    }

    if (DrawButton(250, 320, 300, 50, "Load Adventure")) {
        currentScreen = LOAD;   // Load Game
    }

    if (DrawButton(250, 390, 300, 50, "Run Away From The Dungeons!")) {
        currentScreen = EXIT;  // Quit Game
    }
}

void DrawHeroSelectionScreen(int &currentScreen) {
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
        currentScreen = GAME;  // Move to the game screen (i hope...)
    }
}

bool DrawButton(int x, int y, int width, int height, const char *text) {
    Rectangle buttonBounds = { (float)x, (float)y, (float)width, (float)height };
    bool isHovered = CheckCollisionPointRec(GetMousePosition(), buttonBounds);

    Color buttonColor = isHovered ? DARKGRAY : LIGHTGRAY;
    DrawRectangleRec(buttonBounds, buttonColor);

    int textWidth = MeasureText(text, 20);
    DrawText(text, x + (width - textWidth) / 2, y + (height - 20) / 2, 20, BLACK);

    return isHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}