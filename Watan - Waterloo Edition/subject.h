#ifndef _SUBJECT_H_
#define _SUBJECT_H_

// Include necessary dependencies
#include "observer.h"
#include <vector>

// -----------------------------------------------------------
// Template class for Subject which manages the state and observers
// -----------------------------------------------------------

template <typename StateType> class Subject {

  // Private member variables
  StateType state; // The current state of the subject
  std::vector<Observer<StateType> *> observers; // List of observers

  // Protected methods
protected:
  void setState(StateType newS); // Method to set a new state

  // Public methods
public:
  Subject() = default; // Default constructor

  void attach(Observer<StateType> *o); // Attach an observer
  void detach(Observer<StateType> *o); // Detach an observer
  void notifyObservers();              // Notify all observers
  StateType getState() const;          // Get the current state

  virtual ~Subject() = 0; // Virtual destructor for polymorphism
};

// Destructor definition
template <typename StateType> Subject<StateType>::~Subject() {}

// Set a new state
template <typename StateType>
void Subject<StateType>::setState(StateType newS) {
  this->state = newS;
}

// Attach an observer to the subject
template <typename StateType>
void Subject<StateType>::attach(Observer<StateType> *o) {
  this->observers.emplace_back(o); // Add the observer to the list
}

// Detach an observer from the subject
template <typename StateType>
void Subject<StateType>::detach(Observer<StateType> *o) {
  // Iterate through the list and erase the observer
  for (auto it = this->observers.begin(); it != this->observers.end(); ++it) {
    if (*it == o) { // If found, erase it from the list
      this->observers.erase(it);
      break; // Exit after erasing
    }
  }
}

// Notify all attached observers of state change
template <typename StateType> void Subject<StateType>::notifyObservers() {
  // Iterate through the observers and notify each of the state change
  for (auto o : this->observers) {
    o->notify(*this);
  }
}

// Get the current state
template <typename StateType> StateType Subject<StateType>::getState() const {
  return this->state;
}

#endif
