#include <random>
#include <iostream>
#include "watan.h"

int main(int argc, char *argv[]) {
    Watan* game = nullptr;

    // Check if arguments are provided
    if (argc > 1) {
        std::string arg1 = argv[1];

        // Handle cases with more than two arguments
        if (argc == 3) {
            if (arg1 == "-seed") {
                int seed = std::stoi(argv[2]); 
                game = new Watan(seed);
            } else if (arg1 == "-load" || arg1 == "-board") {
                std::string load = argv[2];
                game = new Watan(load);
            }
        } 
        // Handle cases with four arguments or more
        else {
            if (arg1 == "-seed") {
                int seed = std::stoi(argv[2]);
                std::string load = argv[4];  // Assumes correct input format
                game = new Watan(load, seed);
            } else {
                std::string load = argv[2];
                int seed = std::stoi(argv[4]);
                game = new Watan(load, seed);
            }
        }
    } else {
        // Handle case when no arguments are provided
        std::random_device rd;  // Use random device for seeding
        int seed = rd();  // Generate a random seed
        game = new Watan(seed);  // Initialize the game with random seed
    }

    // Start the game
    game->start();

    // Cleanup: Delete dynamically allocated game object
    delete game;

    return 0;
}
