#include "state.h"

// --------------------------------------------------------
// Operator overload for printing Resource enum values
// --------------------------------------------------------

std::ostream &operator<<(std::ostream &out, const Resource &r) {
  switch(r) {
    case Resource::LUMBER: out << "LUMBER"; break;
    case Resource::WOOL: out << "WOOL"; break;
    case Resource::GRAIN: out << "GRAIN"; break;
    case Resource::ORE: out << "ORE"; break;
    case Resource::BRICK: out << "BRICK"; break;
    case Resource::DESERT: out << "DESERT"; break;
    default: out << "Unknown Resource"; break;
  }
  return out;
}

// --------------------------------------------------------
// String manipulation with Resources
// --------------------------------------------------------

// Concatenate a string with a Resource (string first)
std::string operator+(const std::string &lhs, const Resource &rhs) {
  switch(rhs) {
    case Resource::LUMBER: return lhs + "LUMBER";
    case Resource::WOOL: return lhs + "WOOL";
    case Resource::GRAIN: return lhs + "GRAIN";
    case Resource::ORE: return lhs + "ORE";
    case Resource::BRICK: return lhs + "BRICK";
    case Resource::DESERT: return lhs + "DESERT";
    default: return lhs + "Unknown Resource";  // Fallback for unknown Resource
  }
}

// Concatenate a Resource with a string (Resource first)
std::string operator+(const Resource &lhs, const std::string &rhs) {
  switch(lhs) {
    case Resource::LUMBER: return "LUMBER" + rhs;
    case Resource::WOOL: return "WOOL" + rhs;
    case Resource::GRAIN: return "GRAIN" + rhs;
    case Resource::ORE: return "ORE" + rhs;
    case Resource::BRICK: return "BRICK" + rhs;
    case Resource::DESERT: return "DESERT" + rhs;
    default: return "Unknown Resource" + rhs;  // Fallback for unknown Resource
  }
}

// --------------------------------------------------------
// Operator overload for printing Colour enum values
// --------------------------------------------------------

std::ostream &operator<<(std::ostream &out, const Colour &c) {
  switch(c) {
    case Colour::NoColour: out << "NoColour"; break;
    case Colour::Blue: out << "Blue"; break;
    case Colour::Red: out << "Red"; break;
    case Colour::Orange: out << "Orange"; break;
    case Colour::Yellow: out << "Yellow"; break;
    default: out << "Unknown Colour"; break;
  }
  return out;
}

// --------------------------------------------------------
// String manipulation with Colours
// --------------------------------------------------------

// Concatenate a string with a Colour (string first)
std::string operator+(const std::string &lhs, const Colour &rhs) {
  switch(rhs) {
    case Colour::NoColour: return lhs + "NoColour";
    case Colour::Blue: return lhs + "Blue";
    case Colour::Red: return lhs + "Red";
    case Colour::Orange: return lhs + "Orange";
    case Colour::Yellow: return lhs + "Yellow";
    default: return lhs + "Unknown Colour";  // Fallback for unknown Colour
  }
}

// Concatenate a Colour with a string (Colour first)
std::string operator+(const Colour &lhs, const std::string &rhs) {
  switch(lhs) {
    case Colour::NoColour: return "NoColour" + rhs;
    case Colour::Blue: return "Blue" + rhs;
    case Colour::Red: return "Red" + rhs;
    case Colour::Orange: return "Orange" + rhs;
    case Colour::Yellow: return "Yellow" + rhs;
    default: return "Unknown Colour" + rhs;  // Fallback for unknown Colour
  }
}
