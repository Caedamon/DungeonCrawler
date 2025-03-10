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

void Dungeon::LoadTextures() {
    std::cout << "[DEBUG] Loading dungeon textures..." << std::endl;

    // Walls
    Dungeon_Wall = LoadTexture("assets/Walls/Dungeon_Wall.png");
    if (Dungeon_Wall.id == 0) std::cerr << "[ERROR] Failed to load Dungeon_Wall.png!\n";
    Wall_L_Corner_InvV = LoadTexture("assets/Walls/Wall_L_Corner_InvV.png");
    if (Wall_L_Corner_InvV.id == 0) std::cerr << "[ERROR] Failed to load Wall_L_Corner_InvV.png!\n";
    Wall_L_Corner_L = LoadTexture("assets/Walls/Wall_L_Corner_L.png");
    if (Wall_L_Corner_L.id == 0) std::cerr << "[ERROR] Failed to load Wall_L_Corner_L.png!\n";
    Wall_L_Corner_V = LoadTexture("assets/Walls/Wall_L_Corner_V.png");
    if (Wall_L_Corner_V.id == 0) std::cerr << "[ERROR] Failed to load Wall_L_Corner_V.png!\n";
    Wall_S_Corner_InvV = LoadTexture("assets/Walls/Wall_S_Corner_InvV.png");
    if (Wall_S_Corner_InvV.id == 0) std::cerr << "[ERROR] Failed to load Wall_S_Corner_InvV.png!\n";
    Wall_S_Corner_L = LoadTexture("assets/Walls/Wall_S_Corner_L.png");
    if (Wall_S_Corner_L.id == 0) std::cerr << "[ERROR] Failed to load Wall_S_Corner_L.png!\n";
    Wall_S_Corner_V = LoadTexture("assets/Walls/Wall_S_Corner_V.png");
    if (Wall_S_Corner_V.id == 0) std::cerr << "[ERROR] Failed to load Wall_S_Corner_V.png!\n";

    // Doors
    Iron_Door = LoadTexture("assets/Doors/Iron_Door.png");
    if (Iron_Door.id == 0) std::cerr << "[ERROR] Failed to load Iron_Door.png!\n";
    Metal_Grating_Door = LoadTexture("assets/Doors/Metal_Grating_Door.png");
    if (Metal_Grating_Door.id == 0) std::cerr << "[ERROR] Failed to load Metal_Grating_Door.png!\n";
    Metal_Grating_Door_Cold = LoadTexture("assets/Doors/Metal_Grating_Door_Cold.png");
    if (Metal_Grating_Door_Cold.id == 0) std::cerr << "[ERROR] Failed to load Metal_Grating_Door_Cold.png!\n";
    Portal_Blue = LoadTexture("assets/Doors/Portal_Blue.png");
    if (Portal_Blue.id == 0) std::cerr << "[ERROR] Failed to load Portal_Blue.png!\n";
    Portal_Green = LoadTexture("assets/Doors/Portal_Green.png");
    if (Portal_Green.id == 0) std::cerr << "[ERROR] Failed to load Portal_Green.png!\n";
    Portal_Purple = LoadTexture("assets/Doors/Portal_Purple.png");
    if (Portal_Purple.id == 0) std::cerr << "[ERROR] Failed to load Portal_Purple.png!\n";
    Wooden_Door_1 = LoadTexture("assets/Doors/Wooden_Door_1.png");
    if (Wooden_Door_1.id == 0) std::cerr << "[ERROR] Failed to load Wooden_Door_1.png!\n";
    Wooden_Door_2 = LoadTexture("assets/Doors/Wooden_Door_2.png");
    if (Wooden_Door_2.id == 0) std::cerr << "[ERROR] Failed to load Wooden_Door_2.png!\n";

    // Floors
    Floor_2x1_A = LoadTexture("assets/Floor/Floor_2x1_A.png");
    if (Floor_2x1_A.id == 0) std::cerr << "[ERROR] Failed to load Floor_2x1_A.png!\n";
    Floor_2x1_B = LoadTexture("assets/Floor/Floor_2x1_B.png");
    if (Floor_2x1_B.id == 0) std::cerr << "[ERROR] Failed to load Floor_2x1_B.png!\n";
    Floor_2x2 = LoadTexture("assets/Floor/Floor_2x2.png");
    if (Floor_2x2.id == 0) std::cerr << "[ERROR] Failed to load Floor_2x2.png!\n";
    Floor_4x1_A = LoadTexture("assets/Floor/Floor_4x1_A.png");
    if (Floor_4x1_A.id == 0) std::cerr << "[ERROR] Failed to load Floor_4x1_A.png!\n";
    Floor_4x1_B = LoadTexture("assets/Floor/Floor_4x1_B.png");
    if (Floor_4x1_B.id == 0) std::cerr << "[ERROR] Failed to load Floor_4x1_B.png!\n";
    Floor_4x4 = LoadTexture("assets/Floor/Floor_4x4.png");
    if (Floor_4x4.id == 0) std::cerr << "[ERROR] Failed to load Floor_4x4.png!\n";

    // Stairs
    StairsUpTexture = LoadTexture("assets/Stairs/Stairs_Up.png");
    if (StairsUpTexture.id == 0) std::cerr << "[ERROR] Failed to load Stairs_Up.png!\n";
    StairsDownTexture = LoadTexture("assets/Stairs/Stairs_Down.png");
    if (StairsDownTexture.id == 0) std::cerr << "[ERROR] Failed to load Stairs_Down.png!\n";

    // Traps
    Floor_Spike = LoadTexture("assets/Traps/Floor_Spike.png");
    if (Floor_Spike.id == 0) std::cerr << "[ERROR] Failed to load Floor_Spike.png!\n";
    Floor_Spikes_Sprung = LoadTexture("assets/Traps/Floor_Spikes_Sprung.png");
    if (Floor_Spikes_Sprung.id == 0) std::cerr << "[ERROR] Failed to load Floor_Spikes_Sprung.png!\n";
    Pit_Large = LoadTexture("assets/Traps/Pit_Large.png");
    if (Pit_Large.id == 0) std::cerr << "[ERROR] Failed to load Pit_Large.png!\n";
    Pit_Large_Spikes = LoadTexture("assets/Traps/Pit_Large_Spikes.png");
    if (Pit_Large_Spikes.id == 0) std::cerr << "[ERROR] Failed to load Pit_Large_Spikes.png!\n";
    Pit_Small = LoadTexture("assets/Traps/Pit_Small.png");
    if (Pit_Small.id == 0) std::cerr << "[ERROR] Failed to load Pit_Small.png!\n";
    Pit_Small_Spikes = LoadTexture("assets/Traps/Pit_Small_Spikes.png");
    if (Pit_Small_Spikes.id == 0) std::cerr << "[ERROR] Failed to load Pit_Small_Spikes.png!\n";

    std::cout << "[DEBUG] Dungeon textures loaded successfully!" << std::endl;
}




Dungeon::Dungeon() {
    grid.resize(MAP_HEIGHT, std::vector<char>(MAP_WIDTH, '#'));
    GenerateDungeon();
}

Dungeon::~Dungeon() {
    if (dungeonTexture.id != 0) {
        UnloadRenderTexture(dungeonTexture);
    }
}

void Dungeon::GenerateDungeon() {
    std::cout << "[DEBUG] Entering GenerateDungeon()" << std::endl;

    // Prevent dungeon generation if the size is too small
    if (MAP_WIDTH < 10 || MAP_HEIGHT < 10) {
        std::cerr << "[ERROR] Dungeon size is too small for room generation!" << std::endl;
        return;
    }

    std::random_device rd;
    std::mt19937 rng(rd());

    std::uniform_int_distribution<int> roomDist(6, 10);
    std::uniform_int_distribution<int> widthDist(4, 11);
    std::uniform_int_distribution<int> heightDist(4, 9);

    int numRooms = roomDist(rng);
    std::cout << "[DEBUG] Number of rooms: " << numRooms << std::endl;

    rooms.clear();  // Clear existing rooms

    constexpr int MAX_ROOM_PLACEMENT_ATTEMPTS = 100; // Prevent infinite loops

    for (int i = 0; i < numRooms; i++) {
        int roomWidth = widthDist(rng);
        int roomHeight = heightDist(rng);

        std::cout << "[DEBUG] Creating room " << i << " of size "
                  << roomWidth << "x" << roomHeight << std::endl;

        int x = 0, y = 0;
        bool validPlacement = false;
        int attempts = 0;  // Track room placement attempts

        std::uniform_int_distribution<int> xDist(2, MAP_WIDTH - roomWidth - 3);
        std::uniform_int_distribution<int> yDist(2, MAP_HEIGHT - roomHeight - 3);

        // Try to place the room within the maximum allowed attempts
        while (!validPlacement && attempts < MAX_ROOM_PLACEMENT_ATTEMPTS) {
            attempts++;
            x = xDist(rng);
            y = yDist(rng);

            // Check if the new room overlaps an existing room
            validPlacement = true;
            for (const auto &room : rooms) {
                if ((x < room.x + room.width && x + roomWidth > room.x) &&
                    (y < room.y + room.height && y + roomHeight > room.y)) {
                    validPlacement = false;
                    break;  // Overlapping room found, retrying
                }
            }
        }

        // If room placment fails within  max attempts, skip it
        if (!validPlacement) {
            std::cerr << "[WARNING] Failed to place room after "
                      << MAX_ROOM_PLACEMENT_ATTEMPTS
                      << " attempts. Skipping room " << i << ".\n";
            continue;  // Skip room and move to the next
        }

        std::cout << "[DEBUG] Room " << i << " placed at (" << x << ", " << y << ")" << std::endl;

        // Store the room
        rooms.push_back({x, y, roomWidth, roomHeight});

        // Mark room on grid
        for (int r = y; r < y + roomHeight; r++) {
            for (int c = x; c < x + roomWidth; c++) {
                grid[r][c] = '.';
            }
        }
    }

    // Generate corridors between rooms
    GenerateCorridors();

    // Place stairs in the dungeon
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
            grid[y1][x1] = '.';
            x1 += (x2 > x1) ? 1 : -1;
        }
        while (y1 != y2) {
            grid[y1][x1] = '.';
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

    grid[upY][upX] = '^';  // Player starting stairs
    grid[downY][downX] = 'v';  // Exit stairs

    std::cout << "[DEBUG] Stairs placed at: (" << upX << ", " << upY << ") for '^'" << std::endl;
    std::cout << "[DEBUG] Exit stairs placed at: (" << downX << ", " << downY << ") for 'v'" << std::endl;
}

void Dungeon::RenderToTexture(const Player& player) {
    std::cout << "[DEBUG] Entering RenderToTexture()" << std::endl;

    if (!IsWindowReady()) {
        std::cerr << "[ERROR] RenderToTexture() called before Raylib window initialized!" << std::endl;
        return;
    }

    // Initialize the dungeon texture if not already initialized
    if (dungeonTexture.id == 0) {
        dungeonTexture = LoadRenderTexture(MAP_WIDTH * 32, MAP_HEIGHT * 32);
    }

    BeginTextureMode(dungeonTexture);
    ClearBackground(BLACK);

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            Vector2 position = { (float)(x * 32), (float)(y * 32) };

            // Fog of War: Check if the tile is within the player's vision
            int dx = abs(player.x - x);
            int dy = abs(player.y - y);
            if (dx * dx + dy * dy > player.GetVisionRange() * player.GetVisionRange()) {
                DrawRectangle(position.x, position.y, 32, 32, DARKGRAY);  // Hidden area
                continue;
            }

            // Keep all your existing tile rendering logic
            switch (grid[y][x]) {
                case '.': DrawTexture(floorTexture, position.x, position.y, WHITE); break;
                case '#': DrawTexture(Dungeon_Wall, position.x, position.y, WHITE); break;
                case '^': DrawTexture(stairsUpTexture, position.x, position.y, WHITE); break;
                case 'v': DrawTexture(stairsDownTexture, position.x, position.y, WHITE); break;
                case 'T': DrawTexture(trapTexture, position.x, position.y, WHITE); break;
                case 'D': DrawTexture(doorTexture, position.x, position.y, WHITE); break;
            }
        }
    }

    EndTextureMode();
    std::cout << "[DEBUG] Exiting RenderToTexture()" << std::endl;
}

void Dungeon::Draw(int playerX, int playerY) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            Vector2 position = { (float)(x * 32), (float)(y * 32) };
            Texture2D textureToDraw = Dungeon_Wall;  // Default to wall texture
            bool flipX = false;
            bool flipY = false;

            // **Floor Textures**
            if (grid[y][x] == '.') {
                textureToDraw = Floor_2x2; // Default floor tile
            }
            else if (grid[y][x] == '#') {
                // **Wall Textures**
                bool up = (y > 0 && grid[y - 1][x] == '#');
                bool down = (y < MAP_HEIGHT - 1 && grid[y + 1][x] == '#');
                bool left = (x > 0 && grid[y][x - 1] == '#');
                bool right = (x < MAP_WIDTH - 1 && grid[y][x + 1] == '#');

                if (left && right && up && down) {
                    textureToDraw = Dungeon_Wall;  // Fully surrounded wall
                }
                else if (left && up && !right && !down) {
                    textureToDraw = Wall_L_Corner_L;
                }
                else if (!left && up && right && !down) {
                    textureToDraw = Wall_L_Corner_L;
                    flipX = true;
                }
                else if (left && !up && !right && down) {
                    textureToDraw = Wall_L_Corner_V;
                }
                else if (!left && !up && right && down) {
                    textureToDraw = Wall_L_Corner_V;
                    flipX = true;
                }
                else if (up && down && !left && !right) {
                    textureToDraw = Wall_S_Corner_V;
                }
                else if (left && right && !up && !down) {
                    textureToDraw = Wall_S_Corner_L;
                }
            }
            else if (grid[y][x] == '^') {
                // **Stairs Up**
                textureToDraw = StairsUpTexture;
            }
            else if (grid[y][x] == 'v') {
                // **Stairs Down**
                textureToDraw = StairsDownTexture;
            }
            else if (grid[y][x] == 'D') {
                // **Doors**
                textureToDraw = Wooden_Door_1;
            }
            else if (grid[y][x] == 'M') {
                textureToDraw = Metal_Grating_Door;
            }
            else if (grid[y][x] == 'P') {
                // **Portals**
                textureToDraw = Portal_Purple;
            }
            else if (grid[y][x] == 'T') {
                // **Traps**
                textureToDraw = Floor_Spike;
            }
            else if (grid[y][x] == 'X') {
                textureToDraw = Pit_Small;
            }

            // **Check if the texture is valid before drawing**
            if (textureToDraw.id != 0) {
                Rectangle sourceRect = { 0.0f, 0.0f, (float)textureToDraw.width, (float)textureToDraw.height };
                Rectangle destRect = { position.x, position.y, 32, 32 };
                Vector2 origin = { 0, 0 };

                if (flipX) sourceRect.width *= -1;
                if (flipY) sourceRect.height *= -1;

                DrawTexturePro(textureToDraw, sourceRect, destRect, origin, 0, WHITE);
            } else {
                DrawRectangle(position.x, position.y, 32, 32, RED);  // Draw red box if texture is missing
            }
        }
    }
}

void Dungeon::UnloadTextures() {
    if (floorTexture.id != 0) UnloadTexture(floorTexture);
    if (Dungeon_Wall.id != 0) UnloadTexture(Dungeon_Wall);
    if (Wall_L_Corner_L.id != 0) UnloadTexture(Wall_L_Corner_L);
    if (trapTexture.id != 0) UnloadTexture(trapTexture);
    if (doorTexture.id != 0) UnloadTexture(doorTexture);
    if (stairsUpTexture.id != 0) UnloadTexture(stairsUpTexture);
    if (stairsDownTexture.id != 0) UnloadTexture(stairsDownTexture);

    std::cout << "[DEBUG] Unloaded dungeon textures!" << std::endl;
}