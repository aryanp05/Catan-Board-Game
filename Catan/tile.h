#ifndef _TILE_H_
#define _TILE_H_

#include "state.h"
#include "subject.h"
#include <vector>

class Criterion;

class Tile final : public Subject<TileState> {
private:

  // Fields
  int index;
  int value;

  // resource structure
  Resource resource;
  std::vector<Criterion *> criteria;

  // robber ?!
  bool robber;

public:
  // Constructor
  Tile(int value, Resource resource, std::vector<Criterion *> criteria,
       bool robber = false, int index = 0);

  // Destructor
  ~Tile();

  // Methods
  int getVal() const;
  Resource getResource() const;
  std::vector<Criterion *> getCriteria();

  // getter and setters
  bool hasRobber() const;
  void setRobber(bool overrun);
};

#endif
