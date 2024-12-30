#ifndef _OBSERVER_H_
#define _OBSERVER_H_

// Forward declaration of Subject class with template specialization for
// StateType
template <typename StateType> class Subject;

template <typename StateType> class Observer {
public:
  virtual ~Observer() =
      default; // Moved the destructor to the top to follow a standard ordering

  // Notify method to be implemented by derived classes
  virtual void notify(Subject<StateType> &whoFrom) = 0;
};

#endif
