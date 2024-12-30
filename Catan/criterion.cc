#include "criterion.h"
#include "road.h"

// Constructor: Initializes Criterion with an index, default tier, and no owner
Criterion::Criterion(int index) {
    this->index = index;                    // Set the unique index for this criterion
    this->tier = CritType::Default;    // Default tier is set to "Default"
    this->completedBy = Colour::NoColour;   // No one owns it initially
}

// Destructor: Currently, no special clean-up is needed
Criterion::~Criterion() {}

// Static map for storing the building costs associated with each criterion tier
std::map<CritType, ResourceArray> Criterion::buildingCosts = {
    {CritType::Settlement, ResourceArray{1, 1, 1, 0, 1}},
    {CritType::City, ResourceArray{0, 0, 2, 3, 0}},
    {CritType::Exam, ResourceArray{3, 2, 2, 2, 1}}
};



// Getter: Returns the Colour of the owner (who completed the criterion)
Colour Criterion::getOwner() const {
    return completedBy;
}

// Getter: Returns the list of neighboring criteria
std::vector<Criterion *> Criterion::getNeighbourCriteria() const {
    return neighbourCriteria;
}

// Getter: Returns the list of neighboring roads
std::vector<Road *> Criterion::getNeighbourRoads() const {
    return neighbourRoads;
}

// Getter: Returns the current tier of the criterion
CritType Criterion::getTier() const {
    return tier;
}

// Setter: Sets the owner of the criterion and assigns it to the "Settlement" tier
void Criterion::setOwner(Colour newOwner) {
    completedBy = newOwner;                 // Set the new owner
    setTier(CritType::Settlement);      // Automatically set to "Settlement" tier when owned
}

// Add a neighboring criterion to the list of neighbourCriteria
void Criterion::addNeighbour(Criterion *criterion) {
    this->neighbourCriteria.push_back(criterion);  // Adds a criterion to the list
}

// Add a neighboring road to the list of neighbourroads
void Criterion::addNeighbour(Road *road) {
    this->neighbourRoads.push_back(road);  // Adds a road to the list
}

// Setter: Sets the tier of the criterion and notifies observers about the change
void Criterion::setTier(CritType newTier) {
    tier = newTier;                         // Update the tier
    this->setState(CriterionState{completedBy, index, newTier});  // Update state with the new tier and owner
    this->notifyObservers();                // Notify all observers of the change
}

ResourceArray Criterion::toUpgradeCost(const CritType tier) {
  switch(tier) {
    case CritType::Default: return buildingCosts.at(CritType::Settlement);
    case CritType::Settlement: return buildingCosts.at(CritType::City);
    case CritType::City: return buildingCosts.at(CritType::Exam);
    default: return buildingCosts.at(CritType::Exam);

  }
}

// Static method: Determines if the criterion can be built based on available resources and tier
bool Criterion::canBuild(const ResourceArray &resources, const CritType tier) {
    // Check if the player has enough resources for the given tier
    switch(tier) {
        case CritType::Default:
            return resources.canAfford(buildingCosts.at(CritType::Settlement));
        case CritType::Settlement:
            return resources.canAfford(buildingCosts.at(CritType::City));
        case CritType::City:
            return resources.canAfford(buildingCosts.at(CritType::Exam));
        default:
            return false;  // If no valid tier, return false
    }
}

