#include "raylib.h"
#include "game.h"
#include <iostream>

int main() {
    std::cout << "[DEBUG] main() started." << std::endl;

    // Initialize the game
    Game game;

    std::cout << "[DEBUG] Calling Game::Run()" << std::endl;

    // Run the game loop
    game.Run();

    std::cout << "[DEBUG] Game::Run() finished." << std::endl;

    return 0;
}
