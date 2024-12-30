#ifndef _BOARD_H_
#define _BOARD_H_

#include "criterion.h" // Manages Criterion objects, which represent criteria for game progression
#include "road.h"  // Defines road objects, which represent game objectives
#include "state.h" // Manages game state and colors
#include "tile.h" // Defines Tile class, which represents individual tiles on the board
#include <vector>

class Board {
private:
  // Private member variables that store the tiles, criteria, and roads of the
  // board
  std::vector<Tile *> tileList; // Stores a collection of pointers to Tile objects
  std::vector<Criterion *> criterionList; // Stores a collection of pointers to Criterion objects
  std::vector<Road *> roadList; // Stores a collection of pointers to road objects

public:
  // Constructor to initialize the Board with given tiles, criteria, and roads
  Board(std::vector<Tile *> tileList, std::vector<Criterion *> criterionList,
        std::vector<Road *> roadList);

  // Returns a vector of pointers to all the tiles on the board
  std::vector<Tile *> getTileList() const;

  // Returns a vector of pointers to all the criteria on the board
  std::vector<Criterion *> getCriterionList() const;

  // Returns a vector of pointers to all the roads on the board
  std::vector<Road *> getRoadList() const;

  // Gameplay-related methods that modify the game state based on player actions

  // Places robber on the specified tile and returns the tile
  Tile *placeRobber(size_t tileIdx);

  // Tries to improve a criterion for the specified player (owner)
  bool improve(Colour player, int criterionIdx, bool initialPhase);

  // Returns the current tier of the specified criterion
  CritType getCritType(int criterionIdx) const;

  // Tries to achieve the specified road for the given player (owner)
  bool achieve(Colour player, int roadIdx);

  // Destructor to clean up dynamically allocated memory
  ~Board();
};

#endif // _BOARD_H_
