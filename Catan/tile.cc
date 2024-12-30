#include "tile.h"
#include "criterion.h"

// Constructor
Tile::Tile(int value, Resource resource, std::vector<Criterion *> criteria, bool robber, int index)
		: value{value}, resource{resource}, criteria{criteria}, robber{robber}, index{index} {}

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

// Check if the tile has robber
bool Tile::hasRobber() const {
		return robber;
}

// Set robber presence on the tile and notify observers
void Tile::setRobber(bool overrun) {
		robber = overrun;
		this->setState(TileState{index, robber});
		this->notifyObservers();
}
