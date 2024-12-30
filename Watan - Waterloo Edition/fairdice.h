#ifndef _FAIR_DICE_H_
#define _FAIR_DICE_H_

#include "dice.h" // Include the base class for Dice

// FairDice class, which inherits from Dice
class FairDice final : public Dice {

  // Override the virtual method from Dice class to define how the dice roll
  // works
  int getDiceRoll() override;
};

#endif // _FAIR_DICE_H_
