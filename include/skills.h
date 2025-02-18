#ifndef SKILLS_H
#define SKILLS_H

#include <string>
#include <vector>

struct Skill {
    std::string name;
    std::string description;
};

std::vector<Skill> GetDefaultSkills();

#endif
