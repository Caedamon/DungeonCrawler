#ifndef SKILLS_H
#define SKILLS_H

#include <string>
#include <vector>

class Skill {
public:
    Skill(const std::string& name, const std::string& description);

    // Getters
    const std::string& GetName() const { return name; }
    const std::string& GetDescription() const { return description; }

private:
    std::string name;
    std::string description;
};

// Returns a list of default skills
std::vector<Skill> GetDefaultSkills();

#endif
