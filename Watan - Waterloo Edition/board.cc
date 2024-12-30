#include "board.h"
#include "state.h"

// Constructor to initialize the Board with the provided tiles, criteria, and goals
Board::Board(std::vector<Tile *> tileList, 
             std::vector<Criterion *> criterionList, 
             std::vector<Goal *> goalList)
  : tileList{tileList}, criterionList{criterionList}, goalList{goalList} {
    // Initialization of member variables with the passed arguments
}

// Destructor to clean up dynamically allocated memory for tiles, criteria, and goals
Board::~Board() {

    // Clean up Criterion objects
    for (auto crit : criterionList) {
        delete crit;
    }
    criterionList.clear();

    // Clean up Tile objects
    for (auto t : tileList) {
        delete t;
    }
    tileList.clear();

    // Clean up Goal objects
    for (auto g : goalList) {
        delete g;
    }
    goalList.clear();    
}

// Getter function for retrieving all the tiles on the board
std::vector<Tile *> Board::getTileList() const {
    return tileList;
}

// Getter function for retrieving all the criteria on the board
std::vector<Criterion *> Board::getCriterionList() const {
    return criterionList;
}

// Getter function for retrieving all the goals on the board
std::vector<Goal *> Board::getGoalList() const {
    return goalList;
}

// Attempts to place geese on a given tile by index
Tile *Board::placeGeese(size_t tileIdx) {

    // Check if the tileIdx is within bounds of the tileList vector
    if (tileIdx < tileList.size()) {

        // If the selected tile already has geese, return nullptr (can't place geese here)
        if (tileList.at(tileIdx)->hasGeese()) {
            return nullptr;
        }

        // Cancel the old geese placement on the previous tile
        for (auto &tile : tileList) {
            if (tile->hasGeese()) {
                tile->setGeese(false); // Remove geese from the old tile
                break; // Exit after the first geese is removed
            }
        }

        // Place new geese on the selected tile
        tileList.at(tileIdx)->setGeese(true);

        // Return the tile where geese were placed
        return tileList.at(tileIdx);

    } else {
        // If tileIdx is out of bounds, return nullptr
        return nullptr;
    }
}

// Attempts to achieve a goal for the specified owner (player)
bool Board::achieve(Colour player, int goalIdx) {

    // If the goal is already owned by another player (not "NoColour"), return false
    if (goalList.at(goalIdx)->getOwner() != Colour::NoColour) {
        return false;
    }

    // Check if the goal is adjacent to any owned criteria
    for (auto &criterion : criterionList) {

        for (auto &goal : criterion->getNeighbourGoals()) {

            // If the adjacent goal matches the specified goalIdx
            if (goal->getIndex() == goalIdx) {

                // If the criterion is owned by the current player, the goal can be achieved
                if (criterion->getOwner() == player) {
                    goalList.at(goalIdx)->setOwner(player); // Set the owner of the goal
                    return true; // Successfully achieved the goal
                }

                // If the criterion is not owned by the player, check if any other goal adjacent
                // to this criterion is owned by the player
                for (auto &neighbourGoal : criterion->getNeighbourGoals()) {
                    if (neighbourGoal->getIndex() != goalIdx && neighbourGoal->getOwner() == player) {
                        // If an adjacent goal is owned by the player, the goal can be achieved
                        goalList.at(goalIdx)->setOwner(player);
                        return true;
                    }
                }
            }
        }
    }

    // If no valid conditions were met to achieve the goal, return false
    return false;
}

// Attempts to improve a specified criterion for the given player (owner)
bool Board::improve(Colour player, int criterionIdx, bool initialPhase) {

    // First, check if the criterion is unowned
    if (criterionList.at(criterionIdx)->getOwner() == Colour::NoColour) {

        // If the player is trying to complete this criterion and it is unowned
        // Check if any adjacent criteria are owned by other players
        bool canComplete = true;
        for (auto &neighbour : criterionList.at(criterionIdx)->getNeighbourCriteria()) {
            if (neighbour->getOwner() != Colour::NoColour) {
                canComplete = false;
                break;
            }
        }

        if (canComplete) {
            // If no adjacent criteria are owned by others, the player can own this criterion
            criterionList.at(criterionIdx)->setOwner(player);
            return true;
        } else {
            // If any adjacent criteria are owned by other players, the player cannot complete the criterion
            return false;
        }

    } else if (criterionList.at(criterionIdx)->getOwner() == player) {

        // If the criterion is already owned by the player, check if it can be improved
        CritType currentTier = criterionList.at(criterionIdx)->getTier();

        // The criterion cannot be improved if it's at its maximum level (Exam tier)
        if (currentTier == CritType::Exam) {
            return false;
        }

        // Promote the criterion to the next tier depending on its current tier
        if (currentTier == CritType::Midterm) {
            criterionList.at(criterionIdx)->setTier(CritType::Exam);
            return true;
        } else if (currentTier == CritType::Assignment) {
            criterionList.at(criterionIdx)->setTier(CritType::Midterm);
            return true;
        }
    }

    // If the criterion is owned by another player or can't be improved, return false
    return false;
}
