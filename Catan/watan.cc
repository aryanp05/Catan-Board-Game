#include <sstream>
#include <random>
#include <set>
#include <fstream>
#include <algorithm>
#include "watan.h"
#include "playerinput.h"
#include "resourcearray.h"

using namespace std;

Watan::Watan(unsigned int seed):
  in{new PlayerInput{}},
  turnOrder{{Colour::Blue, Colour::Red, Colour::Orange, Colour::Yellow}},
  gameSeed{seed} {
  // create init conditions
  std::stringstream ss;
  ss << static_cast<int>(this->turnOrder.at(0));
  std::string curTurn = ss.str();
  std::vector<std::string> initialConditions{
    curTurn,
    "0 0 0 0 0 g c",
    "0 0 0 0 0 g c",
    "0 0 0 0 0 g c",
    "0 0 0 0 0 g c",
    generateTileString(gameSeed)
    // no robber at start of game
  };
  loaded = false;
  // init
  this->init(initialConditions); 
}

Watan::Watan(const std::string &loadFilename, unsigned int seed):
  in{new PlayerInput{}},
  turnOrder{{Colour::Blue, Colour::Red, Colour::Orange, Colour::Yellow}},
  gameSeed{seed} {

  std::stringstream ss;
  ss << static_cast<int>(this->turnOrder.at(0));
  std::string curTurn = ss.str();
  
  // load file
  std::ifstream file{loadFilename};
  std::vector<std::string> initialConditions;
  std::string line;
  getline(file, line);
  if (line.find(' ') == std::string::npos) {
    loaded = true;
    // Save file
    initialConditions = {};
    initialConditions.emplace_back(line);
    for (int i = 0 ; i < 5 ; i++) {
      getline(file, line);
      initialConditions.emplace_back(line);
    }
    if(getline(file, line)) {
      initialConditions.emplace_back(line);
    }
  } else {
    loaded = false;
    // Board file
    initialConditions = {
      curTurn,
      "0 0 0 0 0 g c",
      "0 0 0 0 0 g c",
      "0 0 0 0 0 g c",
      "0 0 0 0 0 g c",
      line};
  }
  // init
  this->init(initialConditions);
}


Watan::~Watan() {
  delete td;
  delete in;
  for(auto &stu : this->students) {
    delete stu.second;
  }
  delete board;
}

  std::string Watan::generateTileString(unsigned int seed) const {
      // Probabilities corresponding to dice rolls (2-12, with common rolls appearing more)
      int probs[] = {2, 12, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11};

      // Resource types: LUMBER(0), WOOD(1), GRAIN(2), ORE(3), BRICK(4), DESERT(5)
      // Values represent the counts of each resource
      int resources[] = {4, 4, 4, 3, 3, 3, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 5};

      // Convert probabilities to a vector for shuffling
      std::vector<int> probList(probs, probs + 18);

      // Convert resources into a list with counts represented
      std::vector<int> resourceList;
      for (int i = 0; i < 19; ++i) {
          resourceList.push_back(resources[i]);
      }

      std::default_random_engine generator(seed);

      // Shuffle both lists
      std::shuffle(resourceList.begin(), resourceList.end(), generator);
      std::shuffle(probList.begin(), probList.end(), generator);

      // Build the board string
      std::string board_str;

      for (int i = 0; i < 19; ++i) {
          int resource = resourceList[i];
          board_str += std::to_string(resource) + " ";

          if (resource == 5) { // DESERT: append 7 probability
              board_str += "7 ";
          } else { // Assign a probability from the shuffled probList
              board_str += std::to_string(probList.back()) + " ";
              probList.pop_back(); // Remove the used probability
          }
      }

      return board_str;
}

void Watan::endGame(Colour winner) {
  this->td->displayWinner(winner);
  this->td->promptPlayAgain();
}

// CHECK IMPL HERER
void Watan::loadResources(ResourceArray &rarray, std::stringstream &data) {
  const std::map<Resource, int> &rmap = rarray.getResources();
  
  std::string word;
  for(auto it = rmap.begin();
      it != rmap.end() && (data >> word) && word != "g";
      ++it) {
    std::stringstream ss{word};
    int temp = it->second;
    if(!(ss >> temp)) throw "invalid read of student resource";
  }
}

void Watan::loadRoads(Colour student, std::vector<Road *> roads, std::stringstream &data) {
  std::string line = "";
  while (data >> line && line != "c" && line != "g") {
    roads.at(std::stoi(line))->setOwner(student);
  }
}

void Watan::loadCriteria(Colour student, std::vector<Criterion *> criteria, std::stringstream &data) {
  std::string line = "";
  while (data >> line && line != "c") {
    int index = std::stoi(line);
    this->board->improve(student, index, true);
    data >> line;
    if (std::stoi(line) == 2) {
      this->board->improve(student, index, true);
    } else {
      this->board->improve(student, index, true);
      this->board->improve(student, index, true);
    }
  }
}

void Watan::init(const std::vector<std::string> &initialConditions) { 
  std::stringstream curTurn{initialConditions.at(0)};
  std::stringstream blueData{initialConditions.at(1)};
  std::stringstream redData{initialConditions.at(2)};
  std::stringstream orangeData{initialConditions.at(3)};
  std::stringstream yellowData{initialConditions.at(4)};
  std::stringstream boardData{initialConditions.at(5)};

  delete this->td;
  this->td = new TextDisplay{initialConditions};
  curTurn >> this->firstTurn;

  // default student resources
  ResourceArray blueResources;
  ResourceArray redResources;
  ResourceArray orangeResources;
  ResourceArray yellowResources;

  // parse student resources
  this->loadResources(blueResources, blueData);
  this->loadResources(redResources, redData);
  this->loadResources(orangeResources, orangeData);
  this->loadResources(yellowResources, yellowData);


  // CHECK IMPL HERE
  for(auto &student : this->students) {
    delete student.second;
  }
  delete this->board;
  //

  
  // init students
  this->students = {
    {Colour::Blue, new Student{this, this->td, this->in, Colour::Blue,
      blueResources}},
    {Colour::Red, new Student{this, this->td, this->in, Colour::Red,
      redResources}},
    {Colour::Orange, new Student{this, this->td, this->in, Colour::Orange,
      orangeResources}},
    {Colour::Yellow, new Student{this, this->td, this->in, Colour::Yellow,
      yellowResources}},
  };

  // init roads
  std::vector<Road *> roads;
  for(int i = 0; i < 72; ++i) {
    Road *road = new Road{i};
    roads.emplace_back(road);
    //add td as observer for road
    road->attach(this->td);
  }
  // load roads for students
  this->loadRoads(Colour::Blue, roads, blueData);
  this->loadRoads(Colour::Red, roads, redData);
  this->loadRoads(Colour::Orange, roads, orangeData);
  this->loadRoads(Colour::Yellow, roads, yellowData);

  // init criteria
  std::vector<Criterion *> criteria;
  for(int i = 0; i < 54; ++i) {
    Criterion *crit = new Criterion{i};
    criteria.emplace_back(crit);
    //add td as observer for criterion
    crit->attach(this->td);
  }
  // specify neighbours
  int neighbourCriteria[54][3] = {{1, 3, -1}, {0, 4, -1}, {3, 7, -1}, {0, 2, 8}, {1, 5, 9}, {4, 10, -1}, {7, 12, -1}, {2, 6, 13}, {3, 9, 14}, {4, 8, 15}, {5, 11, 16}, {10, 17, -1}, {6, 18, -1}, {7, 14, 19}, {8, 13, 20}, {9, 16, 21}, {10, 15, 22}, {11, 23, -1}, {12, 19, 24}, {13, 18, 25}, {14, 21, 26}, {15, 20, 27}, {16, 23, 28}, {17, 22, 29}, {18, 30, -1}, {19, 26, 31}, {20, 25, 32}, {21, 28, 33}, {22, 27, 34}, {23, 35, -1}, {24, 31, 36}, {25, 30, 37}, {26, 33, 38}, {27, 32, 39}, {28, 35, 40}, {29, 34, 41}, {30, 42, -1}, {31, 38, 43}, {32, 37, 44}, {33, 40, 45}, {34, 39, 46}, {35, 47, -1}, {36, 43, -1}, {37, 42, 48}, {38, 45, 49}, {39, 44, 50}, {40, 47, 51}, {41, 46, -1}, {43, 49, -1}, {44, 48, 52}, {45, 51, 53}, {46, 50, -1}, {49, 53, -1}, {50, 52, -1}};

  int neighbourRoads[54][3] = {{0, 1, -1}, {0, 2, -1}, {3, 5, -1}, {1, 3, 6}, {2, 4, 7}, {4, 8, -1}, {9, 12, -1}, {5, 9, 13}, {6, 10, 14}, {7, 10, 15}, {8, 11, 16}, {11, 17, -1}, {12, 20, -1}, {13, 18, 21}, {14, 18, 22}, {15, 19, 23}, {16, 19, 24}, {17, 25, -1}, {20, 26, 29}, {21, 26, 30}, {22, 27, 31}, {23, 27, 32}, {24, 28, 33}, {25, 28, 34}, {29, 37, -1}, {30, 35, 38}, {31, 35, 39}, {32, 36, 40}, {33, 36, 41}, {34, 42, -1}, {37, 43, 46}, {38, 43, 47}, {39, 44, 48}, {40, 44, 49}, {41, 45, 50}, {42, 45, 51}, {46, 54, -1}, {47, 52, 55}, {48, 52, 56}, {49, 53, 57}, {50, 53, 58}, {51, 59, -1}, {54, 60, -1}, {55, 60, 63}, {56, 61, 64}, {57, 61, 65}, {58, 62, 66}, {59, 62, -1}, {63, 67, -1}, {64, 67, 69}, {65, 68, 70}, {66, 68, -1}, {69, 71, -1}, {70, 71, -1}};

  //for every criteria
  for(int index = 0; index < 54; ++index){
    //add neighbour criteria
    for(int nbc = 0; nbc < 3; ++nbc){
      if(neighbourCriteria[index][nbc] != -1){
        criteria.at(index)->addNeighbour(criteria.at(neighbourCriteria[index][nbc]));
      }
    }

    //add neighbour Roads
    for(int nbg = 0; nbg < 3; ++nbg){
      if(neighbourRoads[index][nbg] != -1){
        criteria.at(index)->addNeighbour(roads.at(neighbourRoads[index][nbg]));
      }
    }
  }

  // load criteria for students
  this->loadCriteria(Colour::Blue, criteria, blueData);
  this->loadCriteria(Colour::Red, criteria, redData);
  this->loadCriteria(Colour::Orange, criteria, orangeData);
  this->loadCriteria(Colour::Yellow, criteria, yellowData);

  // init tiles
  std::vector<Tile *> tiles{};

  int tileCriteria[19][6] = {{0, 1, 3, 4, 8, 9}, {2, 3, 7, 8, 13, 14}, {4, 5, 9, 10, 15, 16}, {6, 7, 12, 13, 18, 19}, {8, 9, 14, 15, 20, 21}, {10, 11, 16, 17, 22, 23}, {13, 14, 19, 20, 25, 26}, {15, 16, 21, 22, 27, 28}, {18, 19, 24, 25, 30, 31}, {20, 21, 26, 27, 32, 33}, {22, 23, 28, 29, 34, 35}, {25, 26, 31, 32, 37, 38}, {27, 28, 33, 34, 39, 40}, {30, 31, 36, 37, 42, 43}, {32, 33, 38, 39, 44, 45}, {34, 35, 40, 41, 46, 47}, {37, 38, 43, 44, 48, 49}, {39, 40, 45, 46, 50, 51}, {44, 45, 49, 50, 52, 53}};

  // link tiles to criteria and parse boardData
  for(int index = 0; index < 19; ++index){
    int resource;
    int value;
    std::string word;

    // get resource for tile
    boardData >> word;
    std::stringstream stringResource{word};
    if(!(stringResource >> resource)) throw "invalid read for tile resource";
    if(resource < 0 || 5 < resource) throw std::out_of_range("resource must be 0-5");

    // get value for tile
    boardData >> word;
    std::stringstream stringValue{word};
    if(!(stringValue >> value)) throw "invalid read for tile value";
    if((value < 2 || 12 < value) && value != 0) throw std::out_of_range("value must be 2-12 or 0 for DESERT");

    std::vector<Criterion *> criteriaHolder{};
    for(int nbc = 0; nbc < 6; ++nbc){
      criteriaHolder.emplace_back(criteria.at(tileCriteria[index][nbc]));
    }

    Tile *tileHolder = new Tile{value, static_cast<Resource>(resource), criteriaHolder, false, index};
    //add td as observer for tile
    tileHolder->attach(this->td);

    tiles.emplace_back(tileHolder);
  }

  // apply robber if given
  if(initialConditions.size() == 7) {
    std::stringstream robber{initialConditions.at(6)};
    int robberTile = -1;
    if(!(robber >> robberTile)) throw "invalid read for robber pos";
    if(robberTile < 0 || 18 < robberTile) {
      throw std::out_of_range("robber pos must be 0-18 or -1");
    }
    tiles.at(robberTile)->setRobber(true);
  }

  this->attach(this->td); // add td as observer for watan
  for(auto &s : this->students) { // add td as observer for students
    s.second->attach(this->td);
  }


  // init board
  this->board = new Board{tiles, criteria, roads};
}

Colour Watan::whoWon() const {
  for(auto stu : this->students) {
    cout << stu.first << " " << stu.second->hasWon() << endl;
    if(stu.second->hasWon()) {
      return stu.first;
    }
  }
  return Colour::NoColour;
}

bool Watan::start(){
  // firstTurn corresponds to an int value of enum Colour
  // curIndex corresponds to the index of turnOrder
  int curIndex = 0;
  for(size_t i = 0; i < this->turnOrder.size(); ++i) {
    if(static_cast<int>(this->turnOrder.at(i)) == this->firstTurn) {
      curIndex = i;
      break;
    }
  }

  if (!loaded) {
    // beginning of game
    // forward order 1st initial completion
    for(size_t i = 0; i < this->turnOrder.size(); ++i) {
      Student *curStudent = this->students.at(this->turnOrder.at(curIndex));
      this->setState(WatanState{curStudent->getColour()});
      this->notifyObservers();
      bool exit = curStudent->beginTurn(true);
      if (exit) {
        return false;
      }
      ++curIndex;
      if(curIndex >= this->turnOrder.size()) {
        curIndex = 0;
      }
    }
    // reverse order 2nd initial completion
    --curIndex;
    for(size_t i = 0; i < this->turnOrder.size(); ++i) {
      if(curIndex < 0) {
        curIndex = this->turnOrder.size() - 1;
      }
      Student *curStudent = this->students.at(this->turnOrder.at(curIndex));
      this->setState(WatanState{curStudent->getColour()});
      this->notifyObservers();
      bool exit = curStudent->beginTurn(true);
      if (exit) {
        return false;
      }
      --curIndex;
    }
    ++curIndex;
    if(curIndex >= this->turnOrder.size()){
      curIndex = 0;
    }
  }
  //while there is no winner
  while(whoWon() == Colour::NoColour){
    Student *curStudent = this->students.at(this->turnOrder.at(curIndex));
    this->setState(WatanState{curStudent->getColour()});
    this->notifyObservers();
    bool exit = curStudent->beginTurn(false);

    if (exit) {
      return false;
    }

    ++curIndex;
    if(curIndex >= turnOrder.size()){
      curIndex = 0;
    }
  }

  //game ended
  this->td->displayWinner(whoWon());
  this->td->promptPlayAgain();
  return this->in->getResponse() == Response::Yes;
}

  void Watan::loseToRobber() const {
    std::vector<Colour> affectedStudents; // for output
    std::vector<ResourceArray> lost;      // for output

    for (auto s : this->students) {
      // count up student's resources
      
      int resourceCount = s.second->getResources().getTotalResources();

      if (resourceCount >= 10) { // if exceeded, randomly remove a resource till half are removed
        ResourceArray loss;

        // generate ordered set of unique random indices (1...half)
        size_t half = resourceCount / 2;
        
        std::random_device rd; // Create a random device object
        unsigned seed = rd();  // Use it to generate a random seed
        
        std::default_random_engine generator(seed);
        std::uniform_int_distribution<int> distribution(0, 4);

        while (half > 0) {
          int rInt = distribution(generator);
          Resource randomResource = rInt == 0 ? Resource::LUMBER 
                              : rInt == 1 ? Resource::WOOL 
                              : rInt == 2 ? Resource::GRAIN 
                              : rInt == 3 ? Resource::ORE 
                              : rInt == 4 ? Resource::BRICK 
                              : Resource::DESERT;
          
          if (s.second->getResources().canAffordResource(randomResource)) {
            // Subtract the resource and decrease the count
            ResourceArray tempLoss;
            tempLoss.addResource(randomResource, 1);
            s.second->loseResources(tempLoss);
            loss.addResource(randomResource, 1);
            half--;
          } // Close the if statement
        } // Close the while loop

        // apply loss
        // s.second->loseResources(loss);

        // update output
        affectedStudents.emplace_back(s.second->getColour());
        lost.emplace_back(loss);
      } // Close the if (resourceCount >= 10) block
    } // Close the for loop

    this->td->displayRobberRoll(affectedStudents, lost);
  } 


void Watan::steal(Colour robber, Colour target) const{
  // count target's resources
  const ResourceArray &res = this->students.at(target)->getResources();
  int resourceCount = res.getTotalResources();
  if(resourceCount > 0) {
    // generate random index from 1-resourceCount
    
    std::random_device rd; // Create a random device object
    unsigned seed = rd();  // Use it to generate a random seed
    
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(0, 4);

    while(true) {
      int rInt = distribution(generator);
      Resource randomResource = rInt == 0 ? Resource::LUMBER 
                          : rInt == 1 ? Resource::WOOL 
                          : rInt == 2 ? Resource::GRAIN 
                          : rInt == 3 ? Resource::ORE 
                          : rInt == 4 ? Resource::BRICK 
                          : Resource::DESERT;
      if (this->students.at(target)->getResources().canAffordResource(randomResource)) {



        ResourceArray res;
        res.addResource(randomResource, 1);
        
        this->students.at(target)->loseResources(res);
        this->students.at(robber)->gainResources(res);
        this->td->displayStealResult(randomResource, target);
        break;
      }
    }


  }
}

void Watan::distributeResources(int rolledNum) const{
  std::map<Colour, ResourceArray> resourceDistribution = {
  {Colour::Blue, ResourceArray{}},
  {Colour::Red, ResourceArray{}},
  {Colour::Orange, ResourceArray{}},
  {Colour::Yellow, ResourceArray{}}
  };
  for(auto tile : this->board->getTileList()){
    if(tile->getVal() == rolledNum){
      if(tile->hasRobber()){
        continue;
      }
      //this tile gives resources!   
      for(auto criterion : tile->getCriteria()){
        Colour owner = criterion->getOwner();
        //if this criterion is owned by somebody
        if(owner != Colour::NoColour){
          //determine how many resources he gets
          int amt = static_cast<int>(criterion->getTier());
          ResourceArray increment;
          increment.addResource(tile->getResource(), amt);
          resourceDistribution.at(owner).addResource(tile->getResource(), amt);
          
          
          //increase player's resources
          this->students.at(owner)->gainResources(increment);
        }
      }
    }
  }

  if (resourceDistribution.at(Colour::Blue).getTotalResources() + resourceDistribution.at(Colour::Red).getTotalResources() + resourceDistribution.at(Colour::Orange).getTotalResources() + resourceDistribution.at(Colour::Yellow).getTotalResources() == 0) {
    cout << "No students gained resources." << endl << "> ";
  } else {
    if(resourceDistribution.at(Colour::Blue).getTotalResources() > 0) {
      cout << "Student Blue gained:" << endl;
      resourceDistribution.at(Colour::Blue).printResources();
    }
    if(resourceDistribution.at(Colour::Red).getTotalResources() > 0) {
      cout << "Student Red gained:" << endl;
      resourceDistribution.at(Colour::Red).printResources();
    }
    if(resourceDistribution.at(Colour::Orange).getTotalResources() > 0) {
      cout << "Student Orange gained:" << endl;
      resourceDistribution.at(Colour::Orange).printResources();
    }
    if(resourceDistribution.at(Colour::Yellow).getTotalResources() > 0) {
      cout << "Student Yellow gained:" << endl;
      resourceDistribution.at(Colour::Yellow).printResources();
    }
    cout << "> ";
  }
  
 
}

void Watan::giveTo(Colour student, const Resource amount) const {
  ResourceArray trade;
  trade.addResource(amount, 1);
  this->students.at(student)->gainResources(trade);
}

void Watan::takeFrom(Colour student, const Resource amount) const {
  ResourceArray trade;
  trade.addResource(amount, 1);
  this->students.at(student)->loseResources(trade);
}

// CHECK IMPL HERE
std::vector<Colour> Watan::attemptPlaceRobber(Colour attacker, int tileIndex) const {
  std::vector<Colour> stealChoices;
  Tile *tile = this->board->placeRobber(tileIndex);
  if(tile) {
    for(auto &criterion : tile->getCriteria()) { // for each criterion
      Colour owner = criterion->getOwner();
      if(owner != Colour::NoColour && owner != attacker) { // ensure not the attacker
        Student *s = this->students.at(owner);
        const ResourceArray &res = s->getResources();
        const std::map<Resource, int>& resMap = res.getResources();
        for (const auto& pair : resMap) {
        }
        for(auto r : resMap) { // for owner's resources
          if(r.second > 0) { // if they have non-zero resources    

            if (std::find(stealChoices.begin(), stealChoices.end(), owner) == stealChoices.end()) {

              stealChoices.emplace_back(owner);
            }
             // add them as a steal choice
            break;
          }
        }
      } else {
        //stealChoices.emplace_back(Colour::NoColour);
        continue;
      }
      //  else {
      //   stealChoices.emplace_back(Colour::NoColour);
      // }
    }
  } else {
    // stealChoices.emplace_back(Colour::NoColour);
    // LOGIC FOR SAME PLACEMENT
    std::cout << "Can't place on same tile" << std::endl;
      return stealChoices;
    
  }
  if (stealChoices.empty()) {

    stealChoices.emplace_back(Colour::NoColour);
    return stealChoices;
  } 


  return stealChoices;
}


bool Watan::attemptAchieve(Colour owner, int roadIndex) const{
  return this->board->achieve(owner, roadIndex);
}

bool Watan::attemptImprove(Colour owner, int criterionIndex, bool initial) const{
  return this->board->improve(owner, criterionIndex, initial);
}

Criterion* Watan::getCriterion(int criterionIndex) {
  return this->board->getCriterionList().at(criterionIndex);
}

CritType Watan::getCritType(int criterionIndex){
  return this->board->getCriterionList().at(criterionIndex)->getTier();
}

Road* Watan::getRoad(int roadIndex) {
  return this->board->getRoadList().at(roadIndex);
}



void Watan::save(const std::string &saveFilename, const bool rolled, const Colour curStudent) const {
  this->save(std::string{saveFilename}, rolled, curStudent);
}

void Watan::save(const std::string &&saveFilename, const bool rolled, 
const Colour curStudent) const {
  std::ofstream output(saveFilename);
  std::string line;
  switch(curStudent) {
    case Colour::Blue: line = (rolled ? std::to_string(1) : std::to_string(0)); 
    break;
    case Colour::Red: line = (rolled ? std::to_string(2) : std::to_string(1)); 
    break;
    case Colour::Orange: line = (rolled ? std::to_string(3) : std::to_string(2)); 
    break;
    case Colour::Yellow: line = (rolled ? std::to_string(0) : std::to_string(3)); 
    break;
    default: break;
  }
  output << line + "\n";
  output.close();

  std::vector<Road *> roads = this->board->getRoadList();
  std::vector<Criterion *> crits = this->board->getCriterionList();
  std::vector<Tile *> tiles = this->board->getTileList();

  output.open(saveFilename, std::ios_base::app);
  for (Colour t: this->turnOrder) {
    line = "";
    ResourceArray resArray = students.at(t)->getResources();
    line += std::to_string(resArray.getResourceAmount(Resource::LUMBER));
    line += " " + std::to_string(resArray.getResourceAmount(Resource::WOOL));
    line += " " + std::to_string(resArray.getResourceAmount(Resource::GRAIN));
    line += " " + std::to_string(resArray.getResourceAmount(Resource::ORE));
    line += " " + std::to_string(resArray.getResourceAmount(Resource::BRICK));
    line += " g";
    for (Road *&g : roads) {
      if (g->getOwner() == t) {
        line += " " + std::to_string(g->getIndex());
      }
    }

    line += " c";
    for (size_t i = 0 ; i < crits.size() ; i++) {
      if (crits.at(i)->getOwner() == t) {
        line += " " + std::to_string(i);
        switch (crits.at(i)->getTier()) {
          case CritType::Settlement: line += " 1"; break;
          case CritType::City: line += " 2"; break;
          case CritType::Exam: line += " 3"; break;
          default: break;
        }
      }
    }
    output << line + "\n";
  }
  line = "";
  for (int i = 0 ; i < tiles.size() ; i++) {
    int resource = -1;
    switch (tiles.at(i)->getResource()) {
      case Resource::LUMBER: resource = 0; break;
      case Resource::WOOL: resource = 1; break;
      case Resource::GRAIN: resource = 2; break;
      case Resource::ORE: resource = 3; break;
      case Resource::BRICK: resource = 4; break;
      case Resource::DESERT: resource = 5; break;
    }

    line += (i == 0 ? "" : " ") + std::to_string(resource) + " " + 
    std::to_string(tiles.at(i)->getVal());
  }
  output << line + "\n";
  line = "";
  for (size_t i = 0 ; i < tiles.size() ; i++) {
    if (tiles.at(i)->hasRobber()) {
      line = std::to_string(i);
    }
  }

  if (line != "") {
    output << line + "\n";
  }
  output.close();
}
