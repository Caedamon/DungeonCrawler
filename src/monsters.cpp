#include "monsters.h"

std::vector<Monster> GetAllMonsters() {
    return {
            {"Skeleton", "☠", 10, 3, 1.0f},
            {"Goblin", "👾", 8, 2, 1.2f},
            {"Spider", "🕷", 5, 1, 1.5f},
            {"Bat", "🦇", 4, 1, 2.0f},
            {"Snake", "🐍", 12, 4, 1.3f}
    };
}