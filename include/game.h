#ifndef GAME_H
#define GAME_H

#include <vector>
#include "raylib.h"
#include "dungeon.h"
#include "game_state.h"
#include "player.h"
#include "monsters.h"

// Debug mode flag
#define DEBUG_MODE 1  // Change to 0 to disable debug logs

class Game {
public:
    GameState currentState;
    Player player;
    Dungeon dungeon;
    std::vector<Monster> monsters;

    Game();
    void Init();
    void HandleInput();
    void Update();
    void Draw();
    void Run();
    void RenderToTexture();
private:
    RenderTexture2D dungeonTexture;
};

#endif