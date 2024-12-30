#include "road.h"

// Constructor to initialize the Road with a given index
Road::Road(int index) : index{index} {
    owner = Colour::NoColour; // Initially, no one has achieved the Road
}

// Destructor for cleaning up the Road object
Road::~Road() {}

ResourceArray Road::roadCost = ResourceArray{1,0,0,0,1};



// Getter to retrieve the index of the Road
int Road::getIndex() const {
    return index;
}

// Getter to retrieve the owner (owner) of the Road
Colour Road::getOwner() const {
    return owner;
}

// Setter to assign a new owner (owner) to the Road
void Road::setOwner(Colour newOwner) {
    owner = newOwner;  // Update the owner value
    this->setState(RoadState{index, owner}); // Update the state with the new owner
    this->notifyObservers();  // Notify all observers about the state change
}
