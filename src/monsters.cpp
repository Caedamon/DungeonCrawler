#include "monsters.h"
#include "dungeon.h"
#include "player.h"
#include "raylib.h"
#include "iostream"
#include <random>


// Monster Constructor Implementation
Monster::Monster(const std::string& name, const std::string& icon, int x, int y, int health, int attack, float speed)
    : name(name), icon(icon), x(x), y(y), health(health), attack(attack), speed(speed) {}

// Returns a static list of default monsters
std::vector<Monster> GetAllMonsters() {
    return {
        Texture2D Skeleton_Texture = LoadTexture("assets/Skeleton.png");
        Texture2D Spider_Texture = LoadTexture("assets/Giant_Spider.png");
        Texture2D Snake_Texture = LoadTexture("assets/Giant_Worm.png");
    };
}

// Monster Draw Function
void Monster::Draw() {
    Vector2 position = {x * 32.0f, y * 32.0f};  // Adjusted for grid
    Texture2D textureToDraw;

    if (name == "Skeleton") {
        textureToDraw = Skeleton_Texture;
    } else if (name == "Spider") {
        textureToDraw = Spider_Texture;
    } else if (name == "Snake") {
        textureToDraw = Snake_Texture;
    }

    DrawTexture(textureToDraw, position.x, position.y, WHITE);
}

void Monster::TakeDamage(int damage) {
    health -= damage;
    std::cout << "[DEBUG] " << name << " took " << damage << " damage! Remaining health: " << health << std::endl;
}

void Monster::AttackPlayer(Player& player) {
    #if DEBUG_MODE
    std::cout << "[DEBUG] " << name << " attacks player for " << attack << " damage!\n";
    #endif

    player.SetHealth(player.GetHealth() - attack);

    if (player.GetHealth() <= 0) {
    #if DEBUG_MODE
        std::cout << "[DEBUG] Player has been defeated!\n";
    #endif
    }
}

bool Monster::CanSeePlayer(const Player& player, const Dungeon& dungeon) const {
    int dx = player.x - x;
    int dy = player.y - y;

    if (abs(dx) > visionRange || abs(dy) > visionRange) {
        return false;  // Player is out of vision range
    }

    int stepX = (dx > 0) ? 1 : (dx < 0) ? -1 : 0;
    int stepY = (dy > 0) ? 1 : (dy < 0) ? -1 : 0;

    int currentX = x, currentY = y;
    while (currentX != player.x || currentY != player.y) {
        currentX += stepX;
        currentY += stepY;

        if (dungeon.grid[currentY][currentX] == '#' || dungeon.grid[currentY][currentX] == 'D') {
            return false;  // Vision is blocked by a wall or door
        }

        if (currentX == player.x && currentY == player.y) {
            return true;  // Player is visible
        }
    }
    return false;
}

void Monster::MoveTowardsPlayer(Player& player, const Dungeon& dungeon, const std::vector<Monster>& monsters) {
    if (CanSeePlayer(player, dungeon)) {
        // Move toward player
        int dx = (player.x > x) ? 1 : (player.x < x) ? -1 : 0;
        int dy = (player.y > y) ? 1 : (player.y < y) ? -1 : 0;

        int newX = x + dx;
        int newY = y + dy;

        if (dungeon.grid[newY][newX] == '.' || dungeon.grid[newY][newX] == '^' || dungeon.grid[newY][newX] == 'v') {
            bool occupied = false;
            for (const auto& m : monsters) {
                if (m.GetX() == newX && m.GetY() == newY) {
                    occupied = true;
                    break;
                }
            }
            if (!occupied) {
                x = newX;
                y = newY;
            }
        }
    } else {
        // Patrol movement (random walk)
        static std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dirDist(0, 3);
        int dx = 0, dy = 0;

        switch (dirDist(rng)) {
            case 0: dx = 1; break;  // Right
            case 1: dx = -1; break; // Left
            case 2: dy = 1; break;  // Down
            case 3: dy = -1; break; // Up
        }

        int newX = x + dx;
        int newY = y + dy;

        if (dungeon.grid[newY][newX] == '.' || dungeon.grid[newY][newX] == '^' || dungeon.grid[newY][newX] == 'v') {
            bool occupied = false;
            for (const auto& m : monsters) {
                if (m.GetX() == newX && m.GetY() == newY) {
                    occupied = true;
                    break;
                }
            }
            if (!occupied) {
                x = newX;
                y = newY;
            }
        }
    }
}

void Monster::SetDead() {
    isDead = true;
}
