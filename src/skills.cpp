#include "skills.h"

// Skill Constructor Implementation
Skill::Skill(const std::string& name, const std::string& description)
    : name(name), description(description) {}

// Returns a static list of default skills
std::vector<Skill> GetDefaultSkills() {
    static const std::vector<Skill> skills = {
        {"Find Trap", "Detects hidden traps"},
        {"Pick Lock", "Unlocks locked doors"}
    };
    return skills;
}
