#include "player.h"
#include "dungeon.h"
#include "monsters.h"

#include <iostream>
#include <algorithm>
#include <unordered_set>

Player::Player(int startX, int startY) {
    x = startX;
    y = startY;
    health = 10;
    maxHealth = 10;
    attack = 2;
}

bool Player::CanMove(int newX, int newY, const std::vector<Monster>& monsters) {
    return std::none_of(monsters.begin(), monsters.end(),
    [newX, newY](const Monster& m) { return m.GetX() == newX && m.GetY() == newY; });
}

void Player::Move(int dx, int dy, Dungeon &dungeon, const std::vector<Monster>& monsters) {
    int newX = this->x + dx;
    int newY = this->y + dy;

    // Check if movement is within dungeon boundaries
    if (newX >= 0 && newX < MAP_WIDTH && newY >= 0 && newY < MAP_HEIGHT) {
        static const std::unordered_set<std::string> blockedTiles = {"#", "⬆", "⬇"};
        if (blockedTiles.find(dungeon.grid[newY][newX]) == blockedTiles.end() && CanMove(newX, newY, monsters)) {
            this->x = newX;
            this->y = newY;
        }
    }
}

void Player::RegenHealth() {
    health = std::min(health + 1, maxHealth);  // Regenerates 1 HP per turn
    std::cout << "Health: " << health << std::endl;
}
