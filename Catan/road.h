#ifndef _Road_H_
#define _Road_H_

// Include necessary headers
#include "resourcearray.h"
#include "state.h"   // For RoadState and Colour definitions
#include "subject.h" // For Subject base class

// Road class inheriting from Subject<RoadState>
class Road final : public Subject<RoadState> {

private:
  Colour owner; // The Colour (player) who achieved the Road
  int index;         // The unique index of the Road

public:
  static ResourceArray roadCost; // Cost of completing a Road
  // Constructor that initializes the Road with an index

  Road(int index);

  // Destructor for Road
  ~Road();

  // Getter for the owner of the Road (who achieved it)
  Colour getOwner() const;

  // Getter for the index of the Road
  int getIndex() const;

  // Setter to assign a new owner (owner) for the Road
  void setOwner(Colour newOwner);
};

#endif
