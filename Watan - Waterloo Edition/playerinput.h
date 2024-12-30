#ifndef _PLAYER_INPUT_H_
#define _PLAYER_INPUT_H_

#include <string>
#include <vector>

// Enum class for Yes/No responses
enum class Response { Yes, No };

// Enum class to represent different commands that a player can input
enum class Command {
  DiceLoad, // Command for loading dice
  DiceFair, // Command for fair dice
  Roll,     // Command for rolling dice
  Board,    // Command for showing the board
  Status,   // Command for displaying the status
  Criteria, // Command for viewing criteria
  Achieve,  // Command for achieving goals
  Complete, // Command for completing tasks
  Improve,  // Command for improving performance
  Trade,    // Command for trading resources
  Next,     // Command to proceed to the next step
  Save,     // Command to save the game
  Help,     // Command for showing help
  Quit      // Command to quit the game
};

// Forward declaration of Colour enum and detailedTrade struct
struct detailedTrade;

enum class Colour;

// PlayerInput class that handles player input and game state interaction
class PlayerInput {
public:
  // Method to get a colour choice for stealing from the player
  Colour getStealChoice(const std::vector<Colour> &choices);

  // Destructor - no special actions needed
  ~PlayerInput() = default;

  // Method to get a command from the player
  Command getCommand();

  // Method to get the value for a loaded dice roll within a specified range
  int getLoadedDice(const int min, const int max);

  // Method to save the game state to a file
  void saveGameState(const std::string &filename);

  // Method to get the save file name from the player
  std::string getSaveFile();

  // Method to get the tile index from the player
  int getTile(const int min, const int max);

  // Method to get trade details (resources and colour) from the player
  detailedTrade getTrade();

  // Method to get the criterion placement (index) from the player
  int getCriterionPlacement(const int min, const int max);

  // Method to get a Yes/No response from the player
  Response getResponse();

  // Method to get the goal placement (index) from the player
  int getGoalPlacement(const int min, const int max);
};

#endif
