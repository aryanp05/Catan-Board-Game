#ifndef _WATAN_H_
#define _WATAN_H_
#include "board.h"
#include "playerinput.h"
#include "resourcearray.h"
#include "state.h"
#include "student.h"
#include "subject.h"
#include "textdisplay.h"
#include <map>
#include <string>
#include <vector>

class Watan final : public Subject<WatanState> {
private:
  // decider variables
  bool loaded;
  int firstTurn;
  unsigned int gameSeed;

  // layouts and pointers
  std::map<Colour, Student *> students;
  PlayerInput *in = nullptr;
  std::vector<Colour> turnOrder;
  Board *board = nullptr;
  TextDisplay *td = nullptr;

  // loaders
  void loadResources(ResourceArray &rmap, std::stringstream &data);
  void loadRoads(Colour student, std::vector<Road *> roads,
                 std::stringstream &data);
  void loadCriteria(Colour student, std::vector<Criterion *> criteria,
                    std::stringstream &data);

  

  std::string generateTileString(unsigned int seed) const;
  Colour whoWon() const;

public:
  // overloaded constructors
  Watan(unsigned int seed = 1);
  Watan(const std::string &loadFilename, unsigned int seed = 1);

  // destructor
  ~Watan();

  void init(const std::vector<std::string> &initialConditions);
  bool start();
  void loseToRobber() const;
  void steal(Colour robber, Colour target) const;
  void distributeResources(int rolledNum) const;
  void giveTo(Colour student, const Resource amount) const;
  void takeFrom(Colour student, const Resource amount) const;
  std::vector<Colour> attemptPlaceRobber(Colour attacker, int tileIndex) const;

// getters
  Criterion *getCriterion(int criterionIndex);
  CritType getCritType(int criterionIndex);
  Road *getRoad(int roadIndex);

  bool attemptAchieve(Colour owner, int roadIndex) const;
  bool attemptImprove(Colour owner, int criterionIndex, bool initial) const;


  void save(const std::string &saveFilename, const bool rolled,
            const Colour curStudent) const;
  void save(const std::string &&saveFilename, const bool rolled,
            const Colour curStudent) const;

  void endGame(Colour winner);
};

#endif
