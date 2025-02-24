#include "monsters.h"

std::vector<Monster> GetAllMonsters() {
    return {
            {"Skeleton", "☠", 0, 0, 10, 3, 1.0f},
            {"Goblin", "👾", 1, 1, 8, 2, 1.2f},
            {"Spider", "🕷", 2, 2, 5, 1, 1.5f},
            {"Bat", "🦇", 3, 3, 4, 1, 2.0f},
            {"Snake", "🐍", 4, 4, 12, 4, 1.3f}
    };
}
