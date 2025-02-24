#ifndef MONSTERS_H
#define MONSTERS_H

#include <string>
#include <vector>

struct Monster {
    std::string name;
    std::string icon;  // Use string to store Unicode symbols
    int x, y; 
    int health;
    int attack;
    float speed;

    Monster(std::string name, std::string icon, int x, int y, int health, int attack, float speed)
        : name(name), icon(icon), x(x), y(y), health(health), attack(attack), speed(speed) {}
};

// Returns a list of all default monsters
std::vector<Monster> GetAllMonsters();

#endif
