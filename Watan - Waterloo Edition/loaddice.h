#ifndef _LOADED_DICE_H_
#define _LOADED_DICE_H_

// Forward declarations to avoid circular dependency
class PlayerInput;
class TextDisplay;

#include "dice.h"

// The LoadedDice class extends Dice and overrides the roll behavior.
class LoadedDice final : public Dice {
private:
  // Player input handler to interact with the game
  PlayerInput *in;

  // Display handler to update the game view
  TextDisplay *td;

  // Overrides the getDiceRoll to implement custom rolling logic
  int getDiceRoll() override;

public:
  // Constructor to initialize the LoadedDice with input and display
  LoadedDice(PlayerInput *in, TextDisplay *td);
};

#endif
