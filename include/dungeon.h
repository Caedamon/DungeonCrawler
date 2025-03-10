#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>
#include "raylib.h"
#include "dungeon.h"
#include "player.h"

extern const int MAP_WIDTH;
extern const int MAP_HEIGHT;

struct Room {
    int x, y, width, height;
};

class Dungeon {
public:
    Dungeon();   // Constructor
    ~Dungeon();  // Destructor

    void GenerateDungeon();
    void PlaceStairs();
    void GenerateCorridors();
    void RenderToTexture(const Player& player);
    void Draw(int playerX, int playerY);

    void LoadTextures();
    void UnloadTextures();

    std::vector<std::vector<char>> grid;
    std::vector<Room> rooms;
    RenderTexture2D dungeonTexture = {0}; // Stores pre-rendered dungeon map

private:
    // Wall Textures
    Texture2D Dungeon_Wall;
    Texture2D Wall_L_Corner_InvV;
    Texture2D Wall_L_Corner_L;
    Texture2D Wall_L_Corner_V;
    Texture2D Wall_S_Corner_InvV;
    Texture2D Wall_S_Corner_L;
    Texture2D Wall_S_Corner_V;

    // Door Textures
    Texture2D Iron_Door;
    Texture2D Metal_Grating_Door;
    Texture2D Metal_Grating_Door_Cold;
    Texture2D Portal_Blue;
    Texture2D Portal_Green;
    Texture2D Portal_Purple;
    Texture2D Wooden_Door_1;
    Texture2D Wooden_Door_2;

    // Floor Textures
    Texture2D Floor_2x1_A;
    Texture2D Floor_2x1_B;
    Texture2D Floor_2x2;
    Texture2D Floor_4x1_A;
    Texture2D Floor_4x1_B;
    Texture2D Floor_4x4;

    // Stairs
    Texture2D StairsUpTexture;
    Texture2D StairsDownTexture;

    // Traps
    Texture2D Floor_Spike;
    Texture2D Floor_Spikes_Sprung;
    Texture2D Pit_Large;
    Texture2D Pit_Large_Spikes;
    Texture2D Pit_Small;
    Texture2D Pit_Small_Spikes;
};

#endif