#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>
#include <string>
#include "raylib.h"  // Keep this since we use RenderTexture2D

extern const int MAP_WIDTH;
extern const int MAP_HEIGHT;

struct Room {
    int x, y, width, height;
};

struct Dungeon {
    std::vector<std::vector<std::string>> grid;
    std::vector<Room> rooms;
    RenderTexture2D dungeonTexture = {0}; // Stores pre-rendered dungeon map

    Dungeon();
    ~Dungeon();
    void GenerateDungeon();
    void PlaceStairs();
    void GenerateCorridors();
    void Draw();
    void RenderToTexture();
};

#endif
