#ifndef _GOAL_H_
#define _GOAL_H_

// Include necessary headers
#include "resourcearray.h"
#include "state.h"   // For GoalState and Colour definitions
#include "subject.h" // For Subject base class

// Goal class inheriting from Subject<GoalState>
class Goal final : public Subject<GoalState> {

private:
  Colour owner; // The Colour (player) who achieved the Goal
  int index;         // The unique index of the Goal

public:
  static ResourceArray goalCost; // Cost of completing a Goal
  // Constructor that initializes the Goal with an index

  Goal(int index);

  // Destructor for Goal
  ~Goal();

  // Getter for the owner of the Goal (who achieved it)
  Colour getOwner() const;

  // Getter for the index of the Goal
  int getIndex() const;

  // Setter to assign a new owner (owner) for the Goal
  void setOwner(Colour newOwner);
};

#endif
