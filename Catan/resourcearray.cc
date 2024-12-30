#include "resourcearray.h"

// Constructor to initialize the resources
ResourceArray::ResourceArray(int lumber, int wool, int grain, int ore, int brick) {
  resources[Resource::LUMBER] = lumber;
  resources[Resource::WOOL] = wool;
  resources[Resource::GRAIN] = grain;
  resources[Resource::ORE] = ore;
  resources[Resource::BRICK] = brick;
}

// Negates the resource array values by negating each resource from the other array
void ResourceArray::negateResourceArray(const ResourceArray &other) {
  for (const auto &[key, value] : other.resources) {
    // Negate the resource values
    this->resources[key] = -1 * value;
  }
}

// Add a specific amount to the specified resource
void ResourceArray::addResource(Resource res, int amount) {
  resources[res] += amount;
}

// Subtract a specific amount from the specified resource (throws exception if insufficient resources)
void ResourceArray::subtractResource(Resource res, int amount) {
  if (resources[res] < amount) {
    throw std::out_of_range("Insufficient resources to subtract.");
  }
  resources[res] -= amount;
}

// Add another resource array's resources to this one
void ResourceArray::addResourceArray(const ResourceArray &other) {
  for (const auto &[key, value] : other.resources) {
    resources[key] += value;
  }
}

// Subtract another resource array's resources from this one (throws exception if insufficient resources)
void ResourceArray::subtractResourceArray(const ResourceArray &other) {
  for (const auto &[key, value] : other.resources) {
    if (resources[key] < value) {
      throw std::out_of_range("Insufficient resources to subtract.");
    }
    resources[key] -= value;
  }
}

// Get the total amount of resources in the array
int ResourceArray::getTotalResources() const {
  int total = 0;
  for (const auto &[key, value] : resources) {
    total += value; // Add each resource's value
  }
  return total;
}

// Get the amount of a specific resource
int ResourceArray::getResourceAmount(Resource res) const {
  auto it = resources.find(res);
  if (it != resources.end()) {
    return it->second; // Return the resource amount
  }
  return 0; // Return 0 if resource doesn't exist
}

// Check if the array can afford the resources specified in the 'cost' array
bool ResourceArray::canAfford(const ResourceArray &cost) const {
  for (const auto &[key, value] : cost.resources) {
    // If any resource in 'cost' is greater than available resources, return false
    if (resources.at(key) < value) {
      return false;
    }
  }
  return true; // All resources can be afforded
}

// Check if a single resource can be afforded (has at least 1 of the resource)
bool ResourceArray::canAffordResource(Resource cost) {
  if (resources[cost] < 1) {
    return false; // Not enough of the specified resource
  }
  return true; // Can afford the resource
}


// Print only resources with positive amounts
void ResourceArray::printResources() {
  for (const auto& pair : resources) {
    // Only print positive resource values
    if (pair.second > 0) {
      std::cout << pair.second << " " << pair.first << std::endl;
    }
  }
}

// Accessor function to get the resource map
const std::map<Resource, int>& ResourceArray::getResources() const {
  return resources; // Return the map of resources
}

// Equality operator to compare two ResourceArray objects
bool ResourceArray::operator==(const ResourceArray &other) const {
  return resources == other.resources; // Return true if resources match exactly
}
