#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <string>
#include <vector>

struct Equipment {
    std::string name;
    std::string type; // e.g., "Weapon", "Shield"
};

std::vector<Equipment> GetDefaultEquipment();

#endif
