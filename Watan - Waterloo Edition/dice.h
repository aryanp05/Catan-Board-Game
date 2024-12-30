#ifndef _DICE_H_
#define _DICE_H_

// Include state and subject headers first, as they are fundamental to the Dice
// class.
#include "state.h"   // For DiceState
#include "subject.h" // For the Subject class template

// Dice class is derived from the Subject class, which is a template for
// managing observers.
class Dice : public Subject<DiceState> {
private:
  virtual int getDiceRoll() = 0;

public:
  // Constructor: Initializes the Dice object
  Dice();

  // Virtual destructor: Provides a default implementation for cleanup (virtual
  // inheritance)
  virtual ~Dice() = default;

  // Method to roll the dice and return the resulting value
  int roll();
};

#endif // _DICE_H_
