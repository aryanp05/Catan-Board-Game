#include "state.h"

// --------------------------------------------------------
// Operator overload for printing Resource enum values
// --------------------------------------------------------

std::ostream &operator<<(std::ostream &out, const Resource &r) {
  switch(r) {
    case Resource::CAFFEINE: out << "CAFFEINE"; break;
    case Resource::LAB: out << "LAB"; break;
    case Resource::LECTURE: out << "LECTURE"; break;
    case Resource::STUDY: out << "STUDY"; break;
    case Resource::TUTORIAL: out << "TUTORIAL"; break;
    case Resource::NETFLIX: out << "NETFLIX"; break;
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
    case Resource::CAFFEINE: return lhs + "CAFFEINE";
    case Resource::LAB: return lhs + "LAB";
    case Resource::LECTURE: return lhs + "LECTURE";
    case Resource::STUDY: return lhs + "STUDY";
    case Resource::TUTORIAL: return lhs + "TUTORIAL";
    case Resource::NETFLIX: return lhs + "NETFLIX";
    default: return lhs + "Unknown Resource";  // Fallback for unknown Resource
  }
}

// Concatenate a Resource with a string (Resource first)
std::string operator+(const Resource &lhs, const std::string &rhs) {
  switch(lhs) {
    case Resource::CAFFEINE: return "CAFFEINE" + rhs;
    case Resource::LAB: return "LAB" + rhs;
    case Resource::LECTURE: return "LECTURE" + rhs;
    case Resource::STUDY: return "STUDY" + rhs;
    case Resource::TUTORIAL: return "TUTORIAL" + rhs;
    case Resource::NETFLIX: return "NETFLIX" + rhs;
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
