#ifndef _TEXT_DISPLAY_H_
#define _TEXT_DISPLAY_H_

// Include necessary dependencies
#include "gameobservers.h"
#include "resourcearray.h"
#include "state.h"
#include <map>
#include <string>
#include <vector>

// Convert a string letter to another format
std::string convertLetter(const std::string &input);

// Forward declaration for Subject template class
template <typename StateType> class Subject;

// -----------------------------------------------------------
// TextDisplay class manages the display logic for various game states
// -----------------------------------------------------------

class TextDisplay final : public WatanObserver,
                          public StudentObserver,
                          public CriterionObserver,
                          public TileObserver,
                          public GoalObserver,
                          public DiceObserver {

private:
  // Private member variables
  Colour curStudent; // The current student whose turn it is
  std::vector<std::map<Resource, int>>
      studentResources; // Resources for each student
  std::vector<std::vector<std::vector<int>>>
      studentCriteria; // Criteria for each student: Assignment, Midterm, Exam
  std::vector<std::string> boardGoals;    // Board goals
  std::vector<std::string> boardCriteria; // Board criteria
  std::vector<std::string> boardTiles;    // Board tiles
  std::vector<std::string> boardProb;     // Board probabilities
  int geesePos;                           // Position of geese on the board

public:
  // Constructor
  TextDisplay(std::vector<std::string> initialConditions);

  void printSpaces(int n) const;
  void printLineWithIndent(int indent, const std::string &line) const;
  std::string formatCriterion(int index) const;
  std::string formatGoal(int index) const;
  std::string formatTile(int index) const;

  void printWhiteSpace(int num);

  // observer notifications for various states
  void notify(Subject<WatanState> &whoFrom) override;
  void notify(Subject<StudentState> &whoFrom) override;
  void notify(Subject<CriterionState> &whoFrom) override;
  void notify(Subject<TileState> &whoFrom) override;
  void notify(Subject<GoalState> &whoFrom) override;
  void notify(Subject<DiceState> &whoFrom) override;

  // Utility method to sort colours
  void sortColours(std::vector<Colour> &colours) const;

  // displaying game info
  void displayWinner(const Colour winner) const; // Display winner
  void displayCurStudent() const;                // Display current student
  void promptInitialAssignment() const;       // Prompt for initial assignment
  void displayBoard() const;                  // Display the board
  void displayStatus() const;                 // Display status
  void displayCriteria() const;               // Display criteria
  void promptLoadedDice() const;              // Prompt for loaded dice
  void promptTrade(detailedTrade deal) const; // Prompt trade
  void
  displayGainedResource(const std::map<Resource, int> resources,
                        const Colour student) const; // Display gained resources
  void displayNoGainedResources() const;     // Display no gained resources
  void displayInsufficientResources() const; // Display insufficient resources
  void displayInvalidInput() const;          // Display invalid input
  void displayInvalidBuild() const;          // Display invalid build
  void displayInvalidRoll() const;           // Display invalid roll
  void displayInvalidCommand() const;        // Display invalid command
  void promptPlayAgain() const;              // Prompt to play again
  void displayHelp() const;                  // Display help
  void displayNoStealChoices(Colour attacker) const; // Display no steal choices
  void
  displayStealChoices(std::vector<Colour> students); // Display steal choices
  void displayStealResult(const Resource stolen,
                          const Colour student) const; // Display steal result
  void displayGeeseRoll(
      const std::vector<Colour> students,
      const std::vector<ResourceArray> lost) const; // Display geese roll

private:
  // Private default constructor
  TextDisplay();

  // Helper methods for drawing board elements
  void up(int &c, int &t, int &g) const;     // Draw top of board
  void middle(int &c, int &t, int &g) const; // Draw a row of the board
  void down(int &c, int &t, int &g) const;   // Draw bottom of board
};

#endif
