#include "criterion.h"
#include "goal.h"

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
    {CritType::Assignment, ResourceArray{1, 1, 1, 0, 1}},
    {CritType::Midterm, ResourceArray{0, 0, 2, 3, 0}},
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

// Getter: Returns the list of neighboring goals
std::vector<Goal *> Criterion::getNeighbourGoals() const {
    return neighbourGoals;
}

// Getter: Returns the current tier of the criterion
CritType Criterion::getTier() const {
    return tier;
}

// Setter: Sets the owner of the criterion and assigns it to the "Assignment" tier
void Criterion::setOwner(Colour newOwner) {
    completedBy = newOwner;                 // Set the new owner
    setTier(CritType::Assignment);      // Automatically set to "Assignment" tier when owned
}

// Add a neighboring criterion to the list of neighbourCriteria
void Criterion::addNeighbour(Criterion *criterion) {
    this->neighbourCriteria.push_back(criterion);  // Adds a criterion to the list
}

// Add a neighboring goal to the list of neighbourGoals
void Criterion::addNeighbour(Goal *goal) {
    this->neighbourGoals.push_back(goal);  // Adds a goal to the list
}

// Setter: Sets the tier of the criterion and notifies observers about the change
void Criterion::setTier(CritType newTier) {
    tier = newTier;                         // Update the tier
    this->setState(CriterionState{completedBy, index, newTier});  // Update state with the new tier and owner
    this->notifyObservers();                // Notify all observers of the change
}

ResourceArray Criterion::toUpgradeCost(const CritType tier) {
  switch(tier) {
    case CritType::Default: return buildingCosts.at(CritType::Assignment);
    case CritType::Assignment: return buildingCosts.at(CritType::Midterm);
    case CritType::Midterm: return buildingCosts.at(CritType::Exam);
    default: return buildingCosts.at(CritType::Exam);

  }
}

// Static method: Determines if the criterion can be built based on available resources and tier
bool Criterion::canBuild(const ResourceArray &resources, const CritType tier) {
    // Check if the player has enough resources for the given tier
    switch(tier) {
        case CritType::Default:
            return resources.canAfford(buildingCosts.at(CritType::Assignment));
        case CritType::Assignment:
            return resources.canAfford(buildingCosts.at(CritType::Midterm));
        case CritType::Midterm:
            return resources.canAfford(buildingCosts.at(CritType::Exam));
        default:
            return false;  // If no valid tier, return false
    }
}

