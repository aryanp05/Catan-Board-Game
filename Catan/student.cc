#include "student.h"
#include "watan.h"
#include "playerinput.h"
#include "textdisplay.h"
#include "fairdice.h"
#include "loaddice.h"
#include "criterion.h"
#include <random>

Student::Student(
  Watan *watan,
  TextDisplay *td,
  PlayerInput *in,
  Colour colour,
  const ResourceArray &resources
): watan{watan},
  td{td},
  in{in},
  colour{colour},
  resources{resources},
  dice{new FairDice{}} {
    dice->attach(td);
    points = 0;
  }

Student::~Student() {
  delete this->dice;
}

Colour Student::getColour() const {
  return this->colour;
}

ResourceArray Student::getResources() const {
  return this->resources;
}

void Student::gainResources(const ResourceArray &amount) {
  ResourceArray &res = this->resources;
  std::map<Resource, int> temp = res.getResources();
  resources.addResourceArray(amount);
  temp = res.getResources();

  this->setState(StudentState{this->colour, amount.getResources()});
  this->notifyObservers();
}

void Student::loseResources(const ResourceArray &amount) {
  if (!resources.canAfford(amount)) {
    throw std::out_of_range("Insufficient resources");
  }
  resources.subtractResourceArray(amount);


  ResourceArray loss;
  loss.negateResourceArray(amount);
  this->setState(StudentState{this->colour, loss.getResources()});
  this->notifyObservers();
}

bool Student::hasWon() const {
  return this->points == 10;
}

bool Student::canAfford(const ResourceArray &cost) const {
  return resources.canAfford(cost);
}

void Student::pointerCheck() {
  if(!this->watan) throw "no game instance available";
  if(!this->td || !this->in) throw "no i/o available";
}

bool Student::achieveAttempt() {
  pointerCheck();

  int roadIndex = this->in->getRoadPlacement(0, 71);
  Road *road = this->watan->getRoad(roadIndex);

  if(!this->canAfford(road->roadCost)){
    this->td->displayInsufficientResources();
    return false;
  }

  if(!this->watan->attemptAchieve(this->colour, roadIndex)) {
    this->td->displayInvalidBuild();
    return false;
  }

  this->loseResources(road->roadCost);
  this->td->displayBoard();
  return true;
  
}



bool Student::buildAttempt(bool initialTurn) {
  pointerCheck();

  int criterionIndex = this->in->getCriterionPlacement(0, 53);
  CritType tier = this->watan->getCritType(criterionIndex);
  Criterion* c = this->watan->getCriterion(criterionIndex);

  if(tier == CritType::Exam) {
    this->td->displayInvalidBuild();
    return false;
  }

  if(!initialTurn && !c->canBuild(this->resources, tier)) {
    this->td->displayInsufficientResources();
    return false;
  }

  if(!this->watan->attemptImprove(this->colour, criterionIndex, initialTurn)) {
    this->td->displayInvalidBuild();
    return false;
  }

  if(!initialTurn) {
    this->loseResources(c->toUpgradeCost(tier));
    this->td->displayBoard();
  }

  points++;

  if (points == 10) {
    watan->endGame(this->colour);
    if(this->in->getResponse() == Response::Yes) {
      delete watan;
      std::random_device rd;
      int seed = rd(); 
      watan = new Watan(seed);
      watan->start();
    }
  }
  return true;

  
}


void Student::moveRobber() {
  this->watan->loseToRobber();
  while(true) {
    int tileIndex = this->in->getTile(0, 18);
    std::vector<Colour> stealChoices = this->watan->attemptPlaceRobber(this->colour, tileIndex);
    while (stealChoices.empty()) {
      tileIndex = this->in->getTile(0, 18);
      stealChoices = this->watan->attemptPlaceRobber(this->colour, tileIndex);
    }
    if(stealChoices.size()) { // valid tileIndex
      if(stealChoices.at(0) == Colour::NoColour) { // no students to steal from
        this->td->displayNoStealChoices(this->colour);
        return;
      }
      this->td->displayStealChoices(stealChoices);
      // get input colour to steal from
      Colour target = this->in->getStealChoice(stealChoices);
      this->watan->steal(this->colour, target);
      return;
    }
  }
}

void Student::trade() {
  if(!this->watan) throw "no game instance available";
  if(!this->td || !this->in) throw "no i/o available";

  detailedTrade deal = this->in->getTrade();

  if(deal.target == Colour::NoColour) {
    this->td->displayInvalidInput();
    return;
  }
  if(!this->resources.canAffordResource(deal.offer)) {
    this->td->displayInsufficientResources();
    return;
  }

  this->td->promptTrade(deal);
  if(this->in->getResponse() == Response::Yes) {

    ResourceArray gainRes, loseRes;
    loseRes.addResource(deal.offer, 1);
    gainRes.addResource(deal.want, 1);
    this->gainResources(gainRes);
    this->loseResources(loseRes);
    // TakeFrom GiveTo
    this->watan->takeFrom(deal.target, deal.want);
    this->watan->giveTo(deal.target, deal.offer);
  }
  // 
}  



bool Student::beginTurn(bool initialCompletion) {
  pointerCheck();

  this->td->displayBoard();

  if(initialCompletion) {
    while(true) {
      this->td->promptInitialSettlement();
      Command c = this->in->getCommand();
      if (c == Command::Complete) {
        if(this->buildAttempt(true)) {
          return false;
        }
      } else if (c == Command::Quit) {
        return true;
      }
    }
  } else {
    this->td->displayCurStudent();
    bool rolled = false;
    while(true) {
      Command c = this->in->getCommand();
      switch(c) {
        case Command::DiceLoad: {
          Dice *temp = this->dice;
          this->dice = new LoadedDice{this->in, this->td};
          this->dice->attach(this->td);
          delete temp;
          break;
        }
        case Command::DiceFair: {
          Dice *temp = this->dice;
          this->dice = new FairDice{};
          this->dice->attach(this->td);
          delete temp;
          break;
        }
        case Command::Roll: {
          if(rolled) break;
          int diceVal = this->dice->roll();
          if(diceVal == 7) {
            this->moveRobber();
          } else {
            this->watan->distributeResources(diceVal);
          }
          rolled = true;
          break;
        }
        case Command::Board: this->td->displayBoard(); break;
        case Command::Status: this->td->displayStatus(); break;
        case Command::Criteria: this->td->displayCriteria(); break;
        case Command::Achieve: this->achieveAttempt(); break;
        case Command::Complete: this->buildAttempt(false); break;
        case Command::Improve: this->buildAttempt(false); break;
        case Command::Trade: this->trade(); break;
        case Command::Next: if (rolled) {return false;}; break;
        case Command::Save:
          this->watan->save(this->in->getSaveFile(), rolled, this->colour);
          break;
        case Command::Help: this->td->displayHelp(); break;
        case Command::Quit: return true;
      }
    }
  }
}
