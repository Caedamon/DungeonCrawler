#include "player.h"
#include "dungeon.h"
#include "monsters.h"

#include <iostream>
#include <ostream>

Player::Player(int startX, int startY) {
    x = startX;
    y = startY;
    health = 10;
    maxHealth = 10;
    attack = 2;
}

bool Player::CanMove(int newX, int newY, const std::vector<Monster>& monsters) {
    for (const Monster& m : monsters) {
        if (m.x == newX && m.y == newY) {
            return false;
        }
    }
    return true;
}

void Player::Move(int dx, int dy, Dungeon &dungeon, const std::vector<Monster>& monsters) {
    int newX = this->x + dx;
    int newY = this->y + dy;

    // Check if movement is within dungeon boundaries
    if (newX >= 0 && newX < MAP_WIDTH && newY >= 0 && newY < MAP_HEIGHT) {
        if (dungeon.grid[newY][newX] != "#" && CanMove(newX, newY, monsters)) {
            this->x = newX;
            this->y = newY;
        }
    }
}

void Player::RegenHealth() {
    health += 1; //regen 1hp /turn
    if (health > maxHealth) health = maxHealth;
    std::cout << "Health: " << health << std::endl;
}