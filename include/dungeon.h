#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>
#include <string>
#include "raylib.h"
#include "monsters.h"

extern const int MAP_WIDTH;
extern const int MAP_HEIGHT;

struct Room {
    int x, y, width, height;
};

struct Dungeon {
    std::vector<std::vector<std::string>> grid;
    std::vector<Room> rooms;
    RenderTexture2D dungeonTexture = {0}; // Should store the "map" as a pre-rendered dungeon
    Font gameFont = {0};  //Font that supports Unicode

    Dungeon();
    ~Dungeon();
    void GenerateDungeon();
    void PlaceStairs();
    void GenerateCorridors();
    void Draw();
    void RenderToTexture();
    //void PrintDungeon();  // Debugging
};

#endif
