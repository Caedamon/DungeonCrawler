#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <string>
#include <vector>

// Enum for Equipment Types
enum class EquipmentType {
    Weapon,
    Shield,
    Armor
};

class Equipment {
public:
    Equipment(const std::string& name, EquipmentType type);

    // Getters
    const std::string& GetName() const { return name; }
    EquipmentType GetType() const { return type; }

private:
    std::string name;
    EquipmentType type;
};

// Returns a list of default equipment
std::vector<Equipment> GetDefaultEquipment();

#endif
