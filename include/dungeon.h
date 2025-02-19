#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>
#include <string>

const int MAP_WIDTH = 30;
const int MAP_HEIGHT = 20;

struct Dungeon {
    std::vector<std::vector<std::string>> grid;

    Dungeon();
    void GenerateDungeon();
    void PlaceStairs();
    void Draw();
    //void PrintDungeon();  // Debugging
};

#endif
