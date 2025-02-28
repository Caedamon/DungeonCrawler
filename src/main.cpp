#include "raylib.h"
#include "game.h"

int main() {
    InitWindow(800, 600, "Dungeon Crawler");
    InitAudioDevice();
    SetTargetFPS(60);

    Game game;
    game.Run();

    CloseAudioDevice();
    CloseWindow();
    return 0;
}
