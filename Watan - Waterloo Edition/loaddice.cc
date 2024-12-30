#include "loaddice.h"
#include "playerinput.h"
#include "textdisplay.h"

// Constructor initializes the LoadedDice with input and display objects
LoadedDice::LoadedDice(PlayerInput *in, TextDisplay *td)
  : in{in}, td{td} {}

// Method to get a valid dice roll from the player input
int LoadedDice::getDiceRoll() {

  // Ensure that both input and display are available
  if(this->in && this->td) {

    // Start a loop to continuously prompt for a valid dice roll
    while(true) {

      // Prompt user to roll the dice
      this->td->promptLoadedDice();

      // Get the roll value within the range [2, 12]
      int diceVal = this->in->getLoadedDice(2, 12);

      // Check if the roll value is within the valid range
      if(2 <= diceVal && diceVal <= 12) {
        return diceVal;  // Return the valid dice roll
      } else {
        // If the roll is invalid, prompt again
        this->td->displayInvalidRoll();
      }
    }
  }

  // If either input or display is unavailable, throw an error
  throw "no i/o available";
}
