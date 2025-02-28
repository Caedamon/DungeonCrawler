#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>
#include <string>
#include "raylib.h"

extern const int MAP_WIDTH;
extern const int MAP_HEIGHT;

struct Room {
    int x, y, width, height;
};

class Dungeon {
public:
    std::vector<std::vector<std::string>> grid;
    std::vector<Room> rooms;
    RenderTexture2D dungeonTexture = {0}; // Stores pre-rendered dungeon map

    Dungeon();
    ~Dungeon();

    void GenerateDungeon();
    void PlaceStairs();
    void GenerateCorridors();
    void Draw(int playerX, int playerY); // Accepts player position for rendering
    void RenderToTexture();
};

#endif
