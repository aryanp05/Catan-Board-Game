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

  // geese ?!
  bool geese;

public:
  // Constructor
  Tile(int value, Resource resource, std::vector<Criterion *> criteria,
       bool geese = false, int index = 0);

  // Destructor
  ~Tile();

  // Methods
  int getVal() const;
  Resource getResource() const;
  std::vector<Criterion *> getCriteria();

  // getter and setters
  bool hasGeese() const;
  void setGeese(bool overrun);
};

#endif
