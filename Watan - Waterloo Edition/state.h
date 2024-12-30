#ifndef _STATE_H_
#define _STATE_H_

#include <iostream>
#include <map>
#include <string>
#include <vector>

// Enum class for Criterion Tiers
enum class CritType {
  Default = 0,    // Default tier
  Assignment = 1, // Assignment tier
  Midterm = 2,    // Midterm tier
  Exam = 3        // Exam tier
};

// Enum class for Resources
enum class Resource {
  CAFFEINE = 0, // Caffeine resource
  LAB = 1,      // Lab resource
  LECTURE = 2,  // Lecture resource
  STUDY = 3,    // Study resource
  TUTORIAL = 4, // Tutorial resource
  NETFLIX = 5   // Netflix resource
};

// Enum class for Colours
enum class Colour {
  NoColour = -1, // No Colour
  Blue = 0,      // Blue Colour
  Red = 1,       // Red Colour
  Orange = 2,    // Orange Colour
  Yellow = 3     // Yellow Colour
};

// Struct to represent a Trade between two players
struct detailedTrade {
  Resource offer; // The resource being offered
  Colour target;  // The target player
  Resource want;  // The resource being requested

  // Constructor with default values
  detailedTrade(Colour target = Colour::NoColour,
                Resource offer = Resource::CAFFEINE,
                Resource want = Resource::CAFFEINE)
      : target{target}, offer{offer}, want{want} {}
};

// Struct to represent an Improvement made on a Criterion
struct Improvement {
  int index;        // The index of the criterion being improved
  CritType oldTier; // The old tier of the criterion
  CritType newTier; // The new tier of the criterion

  // Constructor with default values
  Improvement(int index = -1, CritType oldTier = CritType::Default,
              CritType newTier = CritType::Default)
      : index{index}, oldTier{oldTier}, newTier{newTier} {}
};

// Base class for State
struct State {
  State() = default;
  virtual ~State() = default;
};

// Derived class representing the state of the game related to the current
// player's turn
struct WatanState : public State {
  Colour curTurn; // Current player's turn (Color)

  // Default constructor
  WatanState() = default;

  // Constructor with initial turn
  WatanState(Colour curTurn) : curTurn{curTurn} {}
};

// Derived class representing the state of the student (player)
struct StudentState : public State {
  Colour appliedTo; // Colour of the player the student applied to
  std::map<Resource, int> resourceChange; // Resources and their changes

  // Default constructor
  StudentState() = default;

  // Constructor with initial applied player and resource changes
  StudentState(Colour appliedTo, std::map<Resource, int> resourceChange)
      : appliedTo{appliedTo}, resourceChange{resourceChange} {}
};

// Derived class representing the state of the dice roll
struct DiceState : public State {
  int diceVal; // Value of the dice roll

  // Default constructor
  DiceState() = default;

  // Constructor with initial dice value
  DiceState(int diceVal) : diceVal{diceVal} {}
};

// Derived class representing the state of a Criterion (criterion tier changes)
struct CriterionState : public State {
  Colour newOwner;  // New owner of the criterion
  int index;        // Index of the criterion
  CritType newTier; // New tier of the criterion

  // Default constructor
  CriterionState() = default;

  // Constructor with initial values
  CriterionState(Colour newOwner, int index, CritType newTier)
      : newOwner{newOwner}, index{index}, newTier{newTier} {}
};

// Derived class representing the state of a Tile
struct TileState : public State {
  int index;     // The index of the tile
  bool hasGeese; // Whether the tile has geese or not

  // Default constructor
  TileState() = default;

  // Constructor with initial values for index and geese status
  TileState(int index, bool hasGeese) : index{index}, hasGeese{hasGeese} {}
};

// Derived class representing the state of a Goal (goal ownership changes)
struct GoalState : public State {
  int index;       // Index of the goal
  Colour newOwner; // New owner of the goal

  // Default constructor
  GoalState() = default;

  // Constructor with initial values
  GoalState(int index, Colour newOwner) : index{index}, newOwner{newOwner} {}
};

// Operator to print Resource to an output stream
std::ostream &operator<<(std::ostream &out, const Resource &r);

// Operator to concatenate a string with a Resource
std::string operator+(const std::string &lhs, const Resource &rhs);

// Operator to concatenate a Resource with a string
std::string operator+(const Resource &lhs, const std::string &rhs);

// Operator to print Colour to an output stream
std::ostream &operator<<(std::ostream &out, const Colour &c);

// Operator to concatenate a string with a Colour
std::string operator+(const std::string &lhs, const Colour &rhs);

// Operator to concatenate a Colour with a string
std::string operator+(const Colour &lhs, const std::string &rhs);

#endif
