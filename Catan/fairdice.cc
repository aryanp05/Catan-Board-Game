#include <random>        // For generating random numbers
#include "fairdice.h"    // Include the FairDice header file

// Override of getDiceRoll function to simulate a fair dice roll (2-12 range)
int FairDice::getDiceRoll() {
    // Initialize random device for obtaining a seed
    std::random_device rd;

    // Use the random device seed to initialize the random engine
    std::default_random_engine generator(rd());

    // Define a uniform distribution that gives values between 2 and 12 (inclusive)
    std::uniform_int_distribution<int> distribution(2, 12);

    // Generate the random value and return it
    return distribution(generator);
}
