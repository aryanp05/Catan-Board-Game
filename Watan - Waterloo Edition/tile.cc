#include "tile.h"
#include "criterion.h"

// Constructor
Tile::Tile(int value, Resource resource, std::vector<Criterion *> criteria, bool geese, int index)
		: value{value}, resource{resource}, criteria{criteria}, geese{geese}, index{index} {}

// Destructor
Tile::~Tile() {}

// Getter for tile value
int Tile::getVal() const {
		return value;
}

// Getter for resource type
Resource Tile::getResource() const {
		return resource;
}

// Getter for criteria associated with the tile
std::vector<Criterion *> Tile::getCriteria() {
		return criteria;
}

// Check if the tile has geese
bool Tile::hasGeese() const {
		return geese;
}

// Set geese presence on the tile and notify observers
void Tile::setGeese(bool overrun) {
		geese = overrun;
		this->setState(TileState{index, geese});
		this->notifyObservers();
}
