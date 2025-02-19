#include "dungeon.h"
#include "raylib.h"
#include <cstdlib>  // For rand()
#include <ctime>    // For random seed
#include <iostream>

Dungeon::Dungeon() {
    grid.resize(MAP_HEIGHT, std::vector<std::string>(MAP_WIDTH, "#"));   // Fill with walls
    GenerateDungeon();
}

void Dungeon::GenerateDungeon() {
    srand(time(0));

    // Randomly create open space (simplified room generation)
    for (int i = 2; i < MAP_HEIGHT - 2; i++) {
        for (int j = 2; j < MAP_WIDTH - 2; j++) {
            if (rand() % 100 < 40) {  // 40% chance to be floor
                grid[i][j] = ".";
            }
        }
    }

    PlaceStairs();
}

void Dungeon::PlaceStairs() {
    int upX, upY, downX, downY;
    do {
        upX = rand() % (MAP_WIDTH - 4) + 2;
        upY = rand() % (MAP_HEIGHT - 4) + 2;
    } while (grid[upY][upX] != ".");

    do {
        downX = rand() % (MAP_WIDTH - 4) + 2;
        downY = rand() % (MAP_HEIGHT - 4) + 2;
    } while (grid[downY][downX] != "." || (downX == upX && downY == upY));

    grid[upY][upX] = "⬆";  // Stairs up
    grid[downY][downX] = "⬇";  // Stairs down
}

void Dungeon::Draw() {
    int tileSize = 20;  // Size of each tile on the screen

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            Color color;

            if (grid[y][x] == "⬆") color = GREEN;
            else if (grid[y][x] == "⬇") color = RED;
            else if (grid[y][x] == "#") color = DARKGRAY;
            else if (grid[y][x] == ".") color = LIGHTGRAY;
            else color = BLACK;

            DrawRectangle(x * tileSize, y * tileSize, tileSize, tileSize, color);
        }
    }
}