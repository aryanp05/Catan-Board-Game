#ifndef _RESOURCE_ARRAY_H_
#define _RESOURCE_ARRAY_H_

#include <map>
#include <iostream>
#include "state.h"

class ResourceArray {
  std::map<Resource, int> resources;

public:
  ResourceArray(int caffeine = 0, int lab = 0, int lecture = 0, int study = 0, int tutorial = 0);

  void negateResourceArray(const ResourceArray &other);

  void addResource(Resource res, int amount);
  void subtractResource(Resource res, int amount);
  void addResourceArray(const ResourceArray &other);
  void subtractResourceArray(const ResourceArray &other);

  // Get the total number of all resources
  int getTotalResources() const;

  // Get the amount of a specific resource
  int getResourceAmount(Resource res) const;

  // Check if this ResourceArray can afford costs
  bool canAfford(const ResourceArray &cost) const;
  bool canAffordResource( Resource cost);

  // Access the internal map (const reference for immutability)
  const std::map<Resource, int>& getResources() const;

  void printResources();
  bool operator==(const ResourceArray &other) const;

  
};

#endif

