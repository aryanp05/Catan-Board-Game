#ifndef _GAME_OBSERVERS_H_
#define _GAME_OBSERVERS_H_

// Include necessary headers
#include "state.h"       // Include state header for different game states
#include "observer.h"    // Include observer base class

// Forward declaration of Subject class template with StateType
template <typename StateType> class Subject;

// Observer for WatanState, inheriting from Observer base class
class WatanObserver : public Observer<WatanState> {
public:
    virtual void notify(Subject<WatanState> &whoFrom) = 0; // Notify method to handle WatanState notifications
    virtual ~WatanObserver() = default; // Destructor
};

// Observer for StudentState, inheriting from Observer base class
class StudentObserver : public Observer<StudentState> {
public:
    virtual void notify(Subject<StudentState> &whoFrom) = 0; // Notify method for StudentState
    virtual ~StudentObserver() = default; // Destructor
};

// Observer for CriterionState, inheriting from Observer base class
class CriterionObserver : public Observer<CriterionState> {
public:
    virtual void notify(Subject<CriterionState> &whoFrom) = 0; // Notify method for CriterionState
    virtual ~CriterionObserver() = default; // Destructor
};

// Observer for TileState, inheriting from Observer base class
class TileObserver : public Observer<TileState> {
public:
    virtual void notify(Subject<TileState> &whoFrom) = 0; // Notify method for TileState
    virtual ~TileObserver() = default; // Destructor
};

// Observer for RoadState, inheriting from Observer base class
class RoadObserver : public Observer<RoadState> {
public:
    virtual void notify(Subject<RoadState> &whoFrom) = 0; // Notify method for RoadState
    virtual ~RoadObserver() = default; // Destructor
};

// Observer for DiceState, inheriting from Observer base class
class DiceObserver : public Observer<DiceState> {
public:
    virtual void notify(Subject<DiceState> &whoFrom) = 0; // Notify method for DiceState
    virtual ~DiceObserver() = default; // Destructor
};

#endif
