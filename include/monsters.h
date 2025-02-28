#ifndef MONSTERS_H
#define MONSTERS_H

#include <string>
#include <vector>
#include "raylib.h"  // Needed for drawing

class Monster {
public:
    Monster(const std::string& name, const std::string& icon, int x, int y, int health, int attack, float speed);

    // Getters
    const std::string& GetName() const { return name; }
    const std::string& GetIcon() const { return icon; }
    int GetX() const { return x; }
    int GetY() const { return y; }
    int GetHealth() const { return health; }
    int GetAttack() const { return attack; }
    float GetSpeed() const { return speed; }

    // Draw the Monster
    void Draw();

private:
    std::string name;
    std::string icon;
    int x, y;
    int health;
    int attack;
    float speed;
};

// Returns a list of all default monsters
std::vector<Monster> GetAllMonsters();

#endif
