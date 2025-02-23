#include "dungeon.h"
#include "raylib.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>

const int MAP_WIDTH = 50;
const int MAP_HEIGHT = 35;

Dungeon::Dungeon() {
    grid.resize(MAP_HEIGHT, std::vector<std::string>(MAP_WIDTH, "#"));
    GenerateDungeon();

    // Load font with explicit Unicode glyphs
    int codepoints[] = { 0x2B06, 0x2B07 }; // Unicode for ⬆ (Up) and ⬇ (Down)
    gameFont = LoadFontEx("resources/NotoSans-Regular.ttf", 32, codepoints, 2);

    if (gameFont.texture.id == 0) {
        std::cerr << "Error: Failed to load font 'NotoSans-Regular.ttf'!" << std::endl;
    } else {
        std::cout << "Font loaded successfully with Unicode glyphs!" << std::endl;
    }

    if (IsWindowReady()) {
        RenderToTexture();
    }
}

Dungeon::~Dungeon() {
    UnloadFont(gameFont);
}

void Dungeon::GenerateDungeon() {
    std::random_device rd;
    std::mt19937 rng(rd());

    std::uniform_int_distribution<int> roomDist(6, 10);
    std::uniform_int_distribution<int> widthDist(4, 11);
    std::uniform_int_distribution<int> heightDist(4, 9);

    int numRooms = roomDist(rng);
    for (int i = 0; i < numRooms; i++) {
        int roomWidth = widthDist(rng);
        int roomHeight = heightDist(rng);
        int x = 0, y = 0;

        bool validPlacement = false;

        while (!validPlacement) {
            std::uniform_int_distribution<int> xDist(2, MAP_WIDTH - roomWidth - 3);
            std::uniform_int_distribution<int> yDist(2, MAP_HEIGHT - roomHeight - 3);

            x = xDist(rng);
            y = yDist(rng);
            validPlacement = true;

            for (const Room &r : rooms) {
                if ((x < r.x + r.width + 2) && (x + roomWidth + 2 > r.x) &&
                    (y < r.y + r.height + 2) && (y + roomHeight + 2 > r.y)) {
                    validPlacement = false;
                    break;
                    }
            }
        }

        Room room = {x, y, roomWidth, roomHeight};
        rooms.push_back(room);

        for (int ry = y; ry < y + roomHeight; ry++) {
            for (int rx = x; rx < x + roomWidth; rx++) {
                grid[ry][rx] = ".";
            }
        }
    }

    GenerateCorridors();
    PlaceStairs();
}

void Dungeon::GenerateCorridors() {
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
    if (rooms.empty()) return;

    Room &firstRoom = rooms[0];
    grid[firstRoom.y + 1][firstRoom.x + 1] = "⬆";

    Room &lastRoom = rooms[rooms.size() - 1];
    grid[lastRoom.y + 1][lastRoom.x + 1] = "⬇";
}

void Dungeon::RenderToTexture() {
    if (!IsWindowReady()) {
        std::cerr << "Error: RenderToTexture() called before Raylib window initialized!" << std::endl;
        return;
    }

    if (dungeonTexture.id != 0) {
        UnloadRenderTexture(dungeonTexture);
    }

    dungeonTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

    BeginTextureMode(dungeonTexture);
    ClearBackground(DARKGRAY);

    float tileSize = static_cast<float>(GetScreenWidth()) / MAP_WIDTH;
    float tileSizeY = static_cast<float>(GetScreenHeight()) / MAP_HEIGHT;
    float tileSizeFinal = (tileSize < tileSizeY) ? tileSize : tileSizeY;

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            Color color;
            std::string symbol = "";

            if (grid[y][x] == "⬆") {
                color = LIGHTGRAY;
                symbol = "⬆";
            }
            else if (grid[y][x] == "⬇") {
                color = LIGHTGRAY;
                symbol = "⬇";
            }
            else if (grid[y][x] == "#") color = DARKGRAY;
            else if (grid[y][x] == ".") color = LIGHTGRAY;
            else color = BLACK;

            DrawRectangle(x * tileSizeFinal, y * tileSizeFinal, tileSizeFinal, tileSizeFinal, color);

            if (!symbol.empty()) {
                std::cout << "Rendering tile at (" << x << ", " << y << ") : " << symbol << std::endl;

                Vector2 textPos = {
                    static_cast<float>(x * tileSizeFinal + tileSizeFinal / 4),
                    static_cast<float>(y * tileSizeFinal + tileSizeFinal / 4)
                };
                DrawTextEx(gameFont, symbol.c_str(), textPos, tileSizeFinal / 2, 1, BLACK);
            }
        }
    }

    EndTextureMode();
}

void Dungeon::Draw() {
    if (dungeonTexture.id == 0) {
        std::cerr << "Warning: Dungeon texture missing, regenerating..." << std::endl;
        RenderToTexture();
    }

    DrawTextureRec(dungeonTexture.texture,
                   (Rectangle){0, 0, (float)GetScreenWidth(), (float)-GetScreenHeight()},
                   (Vector2){0, 0}, WHITE);
}
