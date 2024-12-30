#ifndef _CRITERION_H_
#define _CRITERION_H_

#include "resourcearray.h"
#include "state.h"
#include "student.h"
#include "subject.h"
#include <map>
#include <vector>

class Road;

// Criterion class, inherited from Subject to track CriterionState changes
class Criterion final : public Subject<CriterionState> {
private:
  std::vector<Criterion *> neighbourCriteria; // Adjacent Criteria
  std::vector<Road *> neighbourRoads;         // Adjacent Roads
  Colour completedBy; // Colour that completed the criterion
  CritType tier;      // Tier of the Criterion (e.g., Settlement, City, Exam)
  int index;          // Unique index for identifying the criterion
  static std::map<CritType, ResourceArray>
      buildingCosts; // Cost for building at different tiers

public:
  // Constructor: Initialize Criterion with a unique index
  Criterion(int index);

  // Getter for the owner of the criterion (who completed it)
  Colour getOwner() const;

  // Getter for the list of neighboring criteria
  std::vector<Criterion *> getNeighbourCriteria() const;

  // Getter for the list of neighboring roads
  std::vector<Road *> getNeighbourRoads() const;

  // Setter for the owner of the criterion (who completed it)
  void setOwner(Colour newOwner);

  // Getter for the current tier of the criterion
  CritType getTier() const;

  // Add a neighboring Criterion to this one
  void addNeighbour(Criterion *criterion);

  // Add a neighboring road to this one
  void addNeighbour(Road *road);

  // Setter for the tier of the criterion (Settlement, City, Exam)
  void setTier(CritType newTier);

  static ResourceArray toUpgradeCost(const CritType tier);

  // Static method: Checks if the criterion can be built based on available
  // resources and tier
  static bool canBuild(const ResourceArray &resources, const CritType tier);

// Destructor: Clean up any necessary resources
~Criterion();
};

#endif // _CRITERION_H_
