#include "board.h"
#include "state.h"

// Constructor to initialize the Board with the provided tiles, criteria, and roads
Board::Board(std::vector<Tile *> tileList, 
             std::vector<Criterion *> criterionList, 
             std::vector<Road *> roadList)
  : tileList{tileList}, criterionList{criterionList}, roadList{roadList} {
    // Initialization of member variables with the passed arguments
}

// Destructor to clean up dynamically allocated memory for tiles, criteria, and roads
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

    // Clean up road objects
    for (auto g : roadList) {
        delete g;
    }
    roadList.clear();    
}

// Getter function for retrieving all the tiles on the board
std::vector<Tile *> Board::getTileList() const {
    return tileList;
}

// Getter function for retrieving all the criteria on the board
std::vector<Criterion *> Board::getCriterionList() const {
    return criterionList;
}

// Getter function for retrieving all the roads on the board
std::vector<Road *> Board::getRoadList() const {
    return roadList;
}

// Attempts to place robber on a given tile by index
Tile *Board::placeRobber(size_t tileIdx) {

    // Check if the tileIdx is within bounds of the tileList vector
    if (tileIdx < tileList.size()) {

        // If the selected tile already has robber, return nullptr (can't place robber here)
        if (tileList.at(tileIdx)->hasRobber()) {
            return nullptr;
        }

        // Cancel the old robber placement on the previous tile
        for (auto &tile : tileList) {
            if (tile->hasRobber()) {
                tile->setRobber(false); // Remove robber from the old tile
                break; // Exit after the first robber is removed
            }
        }

        // Place new robber on the selected tile
        tileList.at(tileIdx)->setRobber(true);

        // Return the tile where robber were placed
        return tileList.at(tileIdx);

    } else {
        // If tileIdx is out of bounds, return nullptr
        return nullptr;
    }
}

// Attempts to achieve a road for the specified owner (player)
bool Board::achieve(Colour player, int roadIdx) {

    // If the road is already owned by another player (not "NoColour"), return false
    if (roadList.at(roadIdx)->getOwner() != Colour::NoColour) {
        return false;
    }

    // Check if the road is adjacent to any owned criteria
    for (auto &criterion : criterionList) {

        for (auto &road : criterion->getNeighbourRoads()) {

            // If the adjacent road matches the specified roadIdx
            if (road->getIndex() == roadIdx) {

                // If the criterion is owned by the current player, the road can be achieved
                if (criterion->getOwner() == player) {
                    roadList.at(roadIdx)->setOwner(player); // Set the owner of the road
                    return true; // Successfully achieved the road
                }

                // If the criterion is not owned by the player, check if any other road adjacent
                // to this criterion is owned by the player
                for (auto &neighbourRoad : criterion->getNeighbourRoads()) {
                    if (neighbourRoad->getIndex() != roadIdx && neighbourRoad->getOwner() == player) {
                        // If an adjacent road is owned by the player, the road can be achieved
                        roadList.at(roadIdx)->setOwner(player);
                        return true;
                    }
                }
            }
        }
    }

    // If no valid conditions were met to achieve the road, return false
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
        if (currentTier == CritType::City) {
            criterionList.at(criterionIdx)->setTier(CritType::Exam);
            return true;
        } else if (currentTier == CritType::Settlement) {
            criterionList.at(criterionIdx)->setTier(CritType::City);
            return true;
        }
    }

    // If the criterion is owned by another player or can't be improved, return false
    return false;
}
