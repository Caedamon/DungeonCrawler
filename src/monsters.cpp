#include "monsters.h"
#include "raylib.h"

// Monster Constructor Implementation
Monster::Monster(const std::string& name, const std::string& icon, int x, int y, int health, int attack, float speed)
    : name(name), icon(icon), x(x), y(y), health(health), attack(attack), speed(speed) {}

// Returns a static list of default monsters
std::vector<Monster> GetAllMonsters() {
    return {
            {"Skeleton", "◆", 0, 0, 10, 3, 1.0f},  // Gray Rhombus
            {"Spider", "✶", 2, 2, 5, 1, 1.5f},   // Star
            {"Snake", "$", 4, 4, 12, 4, 1.3f}    // Dollar sign for snake
    };
}

// Monster Draw Function
void Monster::Draw() {
    Vector2 position = {x * 20.0f, y * 20.0f};  // Adjust grid position
    DrawText(icon.c_str(), position.x, position.y, 20, WHITE);  // ✅ Use c_str() for std::string
}
