#ifndef GAME_H
#define GAME_H

#include <vector>
#include "raylib.h"
#include "dungeon.h"
#include "game_state.h"
#include "player.h"
#include "monsters.h"

class Game {
public:
    GameState currentState;
    Player player;
    Dungeon dungeon;
    std::vector<Monster> monsters;

    Game();
    void HandleInput();
    void Update();
    void Draw();
    void Run();
};

#endif