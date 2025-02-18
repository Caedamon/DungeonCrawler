#include "skills.h"

std::vector<Skill> GetDefaultSkills() {
    return {
            {"Find Trap", "Detects hidden traps"},
            {"PickLock", "Unlocks locked doors"}
    };
}
