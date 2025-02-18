#ifndef MONSTERS_H
#define MONSTERS_H

#include <string>
#include <vector>

struct Monster {
    std::string name;
    std::string icon;  // Use string to store Unicode symbols
    int health;
    int attack;
    float speed;
};

// Returns a list of all default monsters
std::vector<Monster> GetAllMonsters();

#endif
