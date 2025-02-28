#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <fstream>
#include <filesystem>

#include "game.h"
#include "dungeon.h"
#include "raylib.h"

const int MAP_WIDTH = 50;
const int MAP_HEIGHT = 35;

Dungeon::Dungeon() {
    grid.resize(MAP_HEIGHT, std::vector<std::string>(MAP_WIDTH, "#"));
    GenerateDungeon();
}

Dungeon::~Dungeon() {
    if (dungeonTexture.id != 0) {
        UnloadRenderTexture(dungeonTexture);
    }
}

void Dungeon::GenerateDungeon() {
    std::cout << "[DEBUG] Entering GenerateDungeon()" << std::endl;

    std::random_device rd;
    std::mt19937 rng(rd());

    std::uniform_int_distribution<int> roomDist(6, 10);
    std::uniform_int_distribution<int> widthDist(4, 11);
    std::uniform_int_distribution<int> heightDist(4, 9);

    int numRooms = roomDist(rng);
    std::cout << "[DEBUG] Number of rooms: " << numRooms << std::endl;

    rooms.clear(); // Clear existing rooms

    for (int i = 0; i < numRooms; i++) {
        int roomWidth = widthDist(rng);
        int roomHeight = heightDist(rng);

        std::cout << "[DEBUG] Creating room " << i << " of size " << roomWidth << "x" << roomHeight << std::endl;

        int x = 0, y = 0;
        bool validPlacement = false;

        while (!validPlacement) {
            std::uniform_int_distribution<int> xDist(2, MAP_WIDTH - roomWidth - 3);
            std::uniform_int_distribution<int> yDist(2, MAP_HEIGHT - roomHeight - 3);

            x = xDist(rng);
            y = yDist(rng);

            // Check if room overlaps existing rooms
            validPlacement = true;
            for (const auto &room : rooms) {
                if ((x < room.x + room.width && x + roomWidth > room.x) &&
                    (y < room.y + room.height && y + roomHeight > room.y)) {
                    validPlacement = false;
                    break;
                }
            }
        }

        std::cout << "[DEBUG] Room " << i << " placed at (" << x << ", " << y << ")" << std::endl;

        // Store room
        rooms.push_back({x, y, roomWidth, roomHeight});

        // Mark room on grid
        for (int r = y; r < y + roomHeight; r++) {
            for (int c = x; c < x + roomWidth; c++) {
                grid[r][c] = ".";  // Floor
            }
        }
    }

    GenerateCorridors();
    PlaceStairs();
    std::cout << "[DEBUG] GenerateDungeon() completed successfully!" << std::endl;
}

void Dungeon::GenerateCorridors() {
    if (rooms.size() < 2) return;

    for (size_t i = 1; i < rooms.size(); i++) {
        Room &prev = rooms[i - 1];
        Room &current = rooms[i];

        int x1 = prev.x + prev.width / 2;
        int y1 = prev.y + prev.height / 2;
        int x2 = current.x + current.width / 2;
        int y2 = current.y + current.height / 2;

        while (x1 != x2) {
            grid[y1][x1] = ".";
            x1 += (x2 > x1) ? 1 : -1;
        }
        while (y1 != y2) {
            grid[y1][x1] = ".";
            y1 += (y2 > y1) ? 1 : -1;
        }
    }
}

void Dungeon::PlaceStairs() {
    if (rooms.empty()) {
        std::cerr << "[ERROR] No rooms available to place stairs!" << std::endl;
        return;
    }

    Room &firstRoom = rooms[0];
    Room &lastRoom = rooms[rooms.size() - 1];

    int upX = firstRoom.x + firstRoom.width / 2;
    int upY = firstRoom.y + firstRoom.height / 2;
    int downX = lastRoom.x + lastRoom.width / 2;
    int downY = lastRoom.y + lastRoom.height / 2;

    grid[upY][upX] = "^";  // Player starting stairs
    grid[downY][downX] = "v";  // Exit stairs

    std::cout << "[DEBUG] Stairs placed at: (" << upX << ", " << upY << ") for '^'" << std::endl;
    std::cout << "[DEBUG] Exit stairs placed at: (" << downX << ", " << downY << ") for 'v'" << std::endl;
}

void Dungeon::RenderToTexture() {
    std::cout << "[DEBUG] Entering RenderToTexture()" << std::endl;

    if (!IsWindowReady()) {
        std::cerr << "[ERROR] RenderToTexture() called before Raylib window initialized!" << std::endl;
        return;
    }

    if (dungeonTexture.id == 0) {
        dungeonTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    }

    BeginTextureMode(dungeonTexture);
    ClearBackground(DARKGRAY);
    EndTextureMode();

    std::cout << "[DEBUG] Exiting RenderToTexture()" << std::endl;
}

void Dungeon::Draw(int playerX, int playerY) {
    static int lastX = -1, lastY = -1;

    // Avoid redundant drawing messages
    if (playerX != lastX || playerY != lastY) {
        std::cout << "[DEBUG] Drawing dungeon..." << std::endl;
        std::cout << "[DEBUG] Drawing player at (" << playerX << ", " << playerY << ")" << std::endl;
        lastX = playerX;
        lastY = playerY;
    }

    if (dungeonTexture.id == 0) {
        std::cerr << "[ERROR] Dungeon texture is not initialized!" << std::endl;
        return;
    }

    DrawTextureRec(dungeonTexture.texture,
                   (Rectangle){0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()},
                   (Vector2){0, 0}, WHITE);

    // Draw player at correct position
    DrawText("¤", playerX * 20, playerY * 20, 20, BLUE);
}