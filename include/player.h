#ifndef PLAYER_H
#define PLAYER_H

#include "monsters.h"

class Dungeon;  // Forward declaration to avoid unnecessary includes

class Player {
public:
    int x, y;

    Player(int startX, int startY);
    void Move(int dx, int dy, Dungeon &dungeon, const std::vector<Monster>& monsters);
    void RegenHealth();

    bool CanMove(int newX, int newY, const std::vector<Monster>& monsters);

    // Getter functions
    int GetHealth() const { return health; }
    int GetAttack() const { return attack; }
    int GetMaxHealth() const { return maxHealth; }

    // Setter functions (optional)
    void SetHealth(int value) { health = value; }
    void SetAttack(int value) { attack = value; }

private:
    int health;
    int attack;
    int maxHealth;
};

#endif
