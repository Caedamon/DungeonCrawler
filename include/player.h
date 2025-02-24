#ifndef PLAYER_H
#define PLAYER_H

#include "dungeon.h"
#include "monsters.h"

class Player {
public:
    int x, y;
    int health;
    int attack;
    int maxHealth;

    Player(int startX, int startY);
    void Move(int dx, int dy, Dungeon &dungeon, const std::vector<Monster>& monsters);
    void RegenHealth();

    bool CanMove(int newX, int newY, const std::vector<Monster>& monsters);
};

#endif
