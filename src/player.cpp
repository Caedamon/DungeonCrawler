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

void Player::Move(int dx, int dy, Dungeon &dungeon, std::vector<Monster>& monsters) {
    int newX = x + dx;
    int newY = y + dy;

    #if DEBUG_MODE
    std::cout << "[DEBUG] Trying to move player from (" << x << ", " << y << ") to (" << newX << ", " << newY << ")" << std::endl;
    #endif

    if (newX >= 0 && newX < MAP_WIDTH && newY < MAP_HEIGHT) {
        char tile = dungeon.grid[newY][newX];

        #if DEBUG_MODE
        std::cout << "[DEBUG] Tile at (" << newX << ", " << newY << "): " << tile << std::endl;
        #endif

        // Check if a monster is in the target location
        for (auto& monster : monsters) {
            if (monster.GetX() == newX && monster.GetY() == newY) {
                #if DEBUG_MODE
                std::cout << "[DEBUG] Player attacked " << monster.GetName() << "!\n";
                #endif
                monster.TakeDamage(attack);

                if (monster.GetHealth() <= 0) {
                    #if DEBUG_MODE
                    std::cout << "[DEBUG] " << monster.GetName() << " was defeated!\n";
                    #endif
                    monster.SetDead();
                }
                return;
            }
        }

        // Move player if not blocked
        if (tile != '#' && tile != '^' && tile != 'v') {
            x = newX;
            y = newY;

            #if DEBUG_MODE
            std::cout << "[DEBUG] Player moved to (" << x << ", " << y << ")" << std::endl;
            #endif
        } else {
            #if DEBUG_MODE
            std::cout << "[DEBUG] Movement blocked at (" << newX << ", " << newY << ")" << std::endl;
            #endif
        }
    }

    // Remove dead monsters from the vector
    monsters.erase(std::remove_if(monsters.begin(), monsters.end(),
        [](const Monster& m) { return m.GetHealth() <= 0; }), monsters.end());
}

void Player::RegenHealth() {
    if (health < maxHealth) {
        health++;
        #if DEBUG_MODE
        std::cout << "[DEBUG] Health increased to " << health << "/" << maxHealth << std::endl;
        #endif
    } else {
        #if DEBUG_MODE
        std::cout << "[DEBUG] Health is already full (" << maxHealth << "/" << maxHealth << ")" << std::endl;
        #endif
    }
}

