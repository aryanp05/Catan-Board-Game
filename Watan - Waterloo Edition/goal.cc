#include "goal.h"

// Constructor to initialize the Goal with a given index
Goal::Goal(int index) : index{index} {
    owner = Colour::NoColour; // Initially, no one has achieved the goal
}

// Destructor for cleaning up the Goal object
Goal::~Goal() {}

ResourceArray Goal::goalCost = ResourceArray{0,0,0,1,1};



// Getter to retrieve the index of the Goal
int Goal::getIndex() const {
    return index;
}

// Getter to retrieve the owner (owner) of the Goal
Colour Goal::getOwner() const {
    return owner;
}

// Setter to assign a new owner (owner) to the Goal
void Goal::setOwner(Colour newOwner) {
    owner = newOwner;  // Update the owner value
    this->setState(GoalState{index, owner}); // Update the state with the new owner
    this->notifyObservers();  // Notify all observers about the state change
}
