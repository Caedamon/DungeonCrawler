#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "dungeon.h"
#include "game_state.h"

class Game {
public:
    Game();  // Constructor
    void Run();  // Main game loop

private:
    GameState currentState;
    Dungeon currentDungeon;

    void HandleInput();
    void Update();
    void Draw();
    void StartNewDungeon();
};

#endif
