#ifndef _STUDENT_H_
#define _STUDENT_H_

#include "subject.h"
#include "resourcearray.h"
#include "state.h"
#include <map>

class PlayerInput;
class TextDisplay;
class Player;
class Criterion;
class Watan;
class Dice;

class Student final : public Subject<StudentState> {
private:
    // Dependencies
    Watan *watan;                    // Pointer to Watan (Game State)
    TextDisplay *td;                  // Pointer to TextDisplay (UI)
    PlayerInput *in;                  // Pointer to PlayerInput (Command handler)
    Dice *dice;                       // Pointer to Dice (Rolling Mechanism)

    // Constants and attributes
    const Colour colour;              // Player's Colour
    ResourceArray resources;          // Player's resources (CAFFEINE, LAB, etc.)
    int points;                        // Player's points in the game


    // Ensures pointers are not null
    void pointerCheck();

    // Negates the resource map, stores the negated quantities in 'negated'
    void negateResourceMap(const std::map<Resource, int> &rmap, 
                           std::map<Resource, int> &negated) const;

    // Determines if the player can afford the given cost
    bool canAfford(const ResourceArray &cost) const;

    // Determines if the player can afford the given resource
    bool achieveAttempt();

    // Performs the build attempt on an initial turn
    bool buildAttempt(bool initialTurn);

    // Activates robber on the board
    void moveRobber();

    // Initiates a trade with another player
    void trade();

public:
    // Constructor to initialize a Student object
    Student(Watan *watan, TextDisplay *td, PlayerInput *in, Colour colour, const ResourceArray &resources);

    // Destructor to clean up the Student object
    ~Student();

    // Returns the player's colour
    Colour getColour() const;

    // Returns the player's resources
    ResourceArray getResources() const;

    // Adds resources to the player's resource pool
    void gainResources(const ResourceArray &amount);

    // Deducts resources from the player's resource pool
    void loseResources(const ResourceArray &amount);

    // Returns whether the player has won the game
    bool hasWon() const;

    // Begins the player's turn, performing initial setup if required
    bool beginTurn(bool initialCompletion);
};

#endif
