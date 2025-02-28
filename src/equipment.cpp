#include "equipment.h"

// Equipment Constructor Implementation
Equipment::Equipment(const std::string& name, EquipmentType type)
    : name(name), type(type) {}

// Returns a static list of default equipment
std::vector<Equipment> GetDefaultEquipment() {
    static const std::vector<Equipment> equipment = {
        {"Iron Sword", EquipmentType::Weapon},
        {"Wooden Shield", EquipmentType::Shield},
        {"Leather Armor", EquipmentType::Armor}
    };
    return equipment;
}
