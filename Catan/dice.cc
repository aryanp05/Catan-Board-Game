#include "dice.h"

// Constructor for Dice class
Dice::Dice() : Subject<DiceState>() {
  // Constructor implementation can be extended if needed
}

// Method to roll the dice
int Dice::roll() {
  // Retrieve the value from the derived class' getDiceRoll implementation
  int rolledValue = getDiceRoll();

  // Update the state of the Dice object with the rolled value
  this->setState(DiceState{rolledValue});

  // Notify all observers about the state change
  this->notifyObservers();

  // Return the value rolled
  return rolledValue;
}
