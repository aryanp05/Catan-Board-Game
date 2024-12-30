#include <sstream>
#include "textdisplay.h"
#include "subject.h"
#include "state.h"
#include <algorithm>
using namespace std;

// from single letter to achievement
std::string convertLetter(const std::string& input) {
    switch (input[0]) { // Assuming input is a single character string
        case 'R':
            return "\033[31mRS\033[0m";
        case 'B':
            return "\033[34mBS\033[0m";
        case 'Y':
            return "\033[38;5;11mYS\033[0m";
        case 'O':
            return "\033[38;5;214mOS\033[0m";
        default:
            return input; // Else case for any other input
    }
}
// Colors using ANSI escape codes
string reset = "\033[0m";      // Reset to default color
string red = "\033[31m";       // Red
string green = "\033[32m";     // Green
string yellow = "\033[38;5;11m";    // Yellow
string blue = "\033[34m";      // Blue
string purple = "\033[35m";    // Purple
string cyan = "\033[36m";      // Cyan
string pink = "\033[95m";      // Pink (bright magenta)

map<string, string> colourMap = {
        {"DESERT", "\033[38;5;52mDESERT\033[0m"},   // Light Pink
        {"GRAIN", "\033[38;5;190mGRAIN\033[0m"},   // Bright Magenta
        {"BRICK", "\033[38;5;214mBRICK\033[0m"}, // Purple
        {"LUMBER", "\033[38;5;22mLUMBER\033[0m"}, // Light Blue
        {"WOOL", "\033[38;5;48mWOOL\033[0m"},           // Green
        {"ORE", "\033[38;5;50mORE\033[0m"}        // Bright Green
};


map<string, string> players = {
    {"RS", "\033[31m"},
    {"RC", "\033[31m"},
    {"RE", "\033[31m"},
    {"BS", "\033[34m"},
    {"BC", "\033[34m"},
    {"BE", "\033[34m"},
    {"OS", "\033[38;5;214m"},
    {"OC", "\033[38;5;214m"},
    {"OE", "\033[38;5;214m"},
    {"YS", "\033[38;5;11m"},
    {"YC", "\033[38;5;11m"},
    {"YE", "\033[38;5;11m"}
};




const string name[6] = {"LUMBER", "WOOL", "ORE", 
"GRAIN", "BRICK", "DESERT"};

void TextDisplay::printWhiteSpace(int num) {
    for (int i = 0 ; i < num; i++) {
        cout << " ";
    }
}

// response messages 
void TextDisplay::displayNoGainedResources() const {
    cout << "No student gained resources." << endl << "> ";

}

void TextDisplay::displayInvalidRoll() const {
    cout << "Invalid roll." << endl << "> ";
}

void TextDisplay::displayInsufficientResources() const {
    cout << "You do not have enough resources." << endl << "> ";
}

void TextDisplay::displayInvalidBuild() const {
  cout << "You cannot build here." << endl;
}

void TextDisplay::displayInvalidInput() const {
    cout << "Invalid input." << endl << "> ";
}

void TextDisplay::displayInvalidCommand() const {
    cout << "Invalid command." << endl << "> ";
}

void TextDisplay::displayStealResult(const Resource stolen,
const Colour student) const {
    cout << "Student " << curStudent << " steals " << stolen <<
     " from student " << student << "." << endl << "> ";
}

void TextDisplay::displayNoStealChoices(Colour attacker) const {
  cout << "Student " << attacker << " has no students to steal from." << endl << "> ";
}

void TextDisplay::displayRobberRoll(const vector<Colour> students,
const vector<ResourceArray> lost) const {
    for (unsigned i = 0 ; i < students.size() ; i++) {
        cout << "Student " << students.at(i) << " loses ";
        int sum = 0;
        sum = lost.at(i).getTotalResources();
        cout << sum << " resources to the robber. They lose:" << endl;
        const std::map<Resource, int> &lostResources = lost.at(i).getResources();
        for (auto &r : lostResources) {
            if (r.second > 0){
                cout << r.second << " " << r.first << endl;
            }
        }
    }
    cout << "Choose where to place ROBBER." << endl << "> ";
}


void TextDisplay::sortColours(std::vector<Colour>& colours) const {
    std::vector<Colour> sortedColours;

    // Define the desired sort order
    std::vector<Colour> order = {Colour::Blue, Colour::Red, Colour::Orange, Colour::Yellow};

    // Check for each colour in the desired order and add it to the sortedColours if it exists
    for (const auto& colour : order) {
        if (std::find(colours.begin(), colours.end(), colour) != colours.end()) {
            sortedColours.emplace_back(colour);
        }
    }

    // Optionally assign the result back to the original vector
    colours = sortedColours;
}

// default constructor for TextDisplay
TextDisplay::TextDisplay() {
    //Setting up the default board layout
    vector<int> probs = {3, 10, 5, 4, 0, 10, 11, 3, 8, 2, 6, 8, 12, 5, 11, 4, 6, 9, 9};
    for (int i = 0 ; i < 54 ; i++) {
        if (i < 10) {
            boardCriteria.push_back(" " + to_string(i));
        } else {
            boardCriteria.push_back(to_string(i));
        }

    }
    for (int i = 0 ; i < 72 ; i++) {
        if (i < 10) {
            boardRoads.push_back(" " + to_string(i));
        } else {
            boardRoads.push_back(to_string(i));
        }
    }
    for (int i = 0 ; i < 19 ; i++) {
        if (probs.at(i) == 0) {
            boardProb.push_back("  ");
        } else if (probs.at(i) < 10) {
            boardProb.push_back(" " + to_string(probs.at(i)));
        }
        else {
            boardProb.push_back(to_string(probs.at(i)));
        }
    }

    for (int i = 0 ; i < 19 ; i++) {
        if (i == 7 || i == 9 || i == 10) {
            boardTiles.push_back(name[0]);
        } else if (i == 1 || i == 3 || i == 11 || i == 13) {
            boardTiles.push_back(name[1]);
        } else if (i == 4) {
            boardTiles.push_back(name[5]);
        } else if (i == 5 || i == 8) {
            boardTiles.push_back(name[2]);
        } else if (i == 12 || i == 14 || i == 16) {
            boardTiles.push_back(name[4]);
        } else {
            boardTiles.push_back(name[3]);
        }
    }

    //Setting the resourse count to zero or each player:
    for (int i = 0 ; i < 4 ; i++){
        map<Resource, int> temp_1 = {{Resource::LUMBER, 0},
        {Resource::WOOL, 0}, {Resource::GRAIN, 0}, {Resource::ORE, 0},
        {Resource::BRICK, 0}};
        vector<vector<int>> temp_3 = {{}};
        studentResources.push_back(temp_1);
        studentCriteria = {{}, {}, {}, {}};
    }

    robberPos = -1;
}

TextDisplay::TextDisplay(vector<string> initialConditions): TextDisplay() {
    if (initialConditions.size() != 7 && initialConditions.size() != 6) {
        cout << "Invalid Save File" << endl << "> ";
        return;
    }
    if (stoi(initialConditions.at(0)) == 0) {
        curStudent = Colour::Blue;
    } else if (stoi(initialConditions.at(0)) == 1) {
        curStudent = Colour::Red;
    } else if (stoi(initialConditions.at(0)) == 2) {
        curStudent = Colour::Orange;
    } else if (stoi(initialConditions.at(0)) == 3) {
        curStudent = Colour::Yellow;
    }

    for (int i = 0 ; i < 4 ; i++) {
        string player;
        switch(i) {
            case 0: player = 'B'; break;
            case 1: player = 'R'; break;
            case 2: player = 'O'; break;
            case 3: player = 'Y'; break;
        }

        stringstream ss(initialConditions.at(i+1));
        string word;

        ss >> word;
        studentResources.at(i).at(Resource::LUMBER) = stoi(word);

        ss >> word;
        studentResources.at(i).at(Resource::WOOL) = stoi(word);

        ss >> word;
        studentResources.at(i).at(Resource::GRAIN) = stoi(word);

        ss >> word;
        studentResources.at(i).at(Resource::ORE) = stoi(word);

        ss >> word;
        studentResources.at(i).at(Resource::BRICK) = stoi(word);

        ss >> word;
        if (word != "g") {
            cerr << "Invalid save file" << endl << "> ";
        }

        ss >> word;
        while (word != "c") {

            boardRoads.at(stoi(word)) = player + " ";
        }

        while (ss >> word) {
            int index = stoi(word);
            ss >> word;
            string crit_tier;
            switch (stoi(word)) {
                case 1: crit_tier = 'A'; break;
                case 2: crit_tier = 'M'; break;
                case 3: crit_tier = 'E'; break;
            }
            boardCriteria.at(index) = player + crit_tier;

            if (studentCriteria.at(i).size() == 0) {
                studentCriteria.at(i).push_back({stoi(word), 1});
            }

            if (studentCriteria.at(i).at(studentCriteria.at(i).size() - 1).at(0) == stoi(word)) {
                studentCriteria.at(i).at(studentCriteria.at(i).size() - 1).at(1)++;
            } else {
                studentCriteria.at(i).push_back({stoi(word), 1});
            }
        }
    }
    stringstream ss(initialConditions.at(5));
    int num;
    for (int i = 0 ; i < 19 ; i++) {
        ss >> num;
        switch (num) {
            case 0: boardTiles.at(i) = "LUMBER"; break;
            case 1: boardTiles.at(i) = "WOOL"; break;
            case 2: boardTiles.at(i) = "GRAIN"; break;
            case 3: boardTiles.at(i) = "ORE"; break;
            case 4: boardTiles.at(i) = "BRICK"; break;
            case 5: boardTiles.at(i) = "DESERT"; break;
        }
        ss >> num;
        if (num == 0 || num == 7) {
            boardProb.at(i) = "  ";
            continue;
        }
        boardProb.at(i) = (num < 10 ? " " + to_string(num) : to_string(num));
    }
    if (initialConditions.size() == 7) {
        robberPos = stoi(initialConditions.at(6));
    } else {
        robberPos = -1;
    }
}

void TextDisplay::displayWinner(const Colour winner) const {
    cout << "Student " << winner << " won!" << endl;
}

void TextDisplay::displayCurStudent() const {
    cout << "Student " << curStudent << "'s turn." << endl;
    cout << curStudent << " has ";

    int index = -1, sum_crit = 0;
    if (curStudent == Colour::Blue) {
        index = 0;
    } else if (curStudent == Colour::Red) {
        index = 1;
    } else if (curStudent == Colour::Orange) {
        index = 2;
    } else if (curStudent == Colour::Yellow) {
        index = 3;
    } else {
        throw std::runtime_error("Index not properly initalized");
    }

    for (auto &i : studentCriteria.at(index)) {
        sum_crit += i.at(1);
    }
    cout << sum_crit << " victory points, " << 
    studentResources.at(index).at(Resource::LUMBER) << " lumbers, " <<
    studentResources.at(index).at(Resource::WOOL) << " wools, " <<
    studentResources.at(index).at(Resource::GRAIN) << " grains, " <<
    studentResources.at(index).at(Resource::ORE) << " ores, and " <<
    studentResources.at(index).at(Resource::BRICK) << "  bricks." << endl << "> ";

}

void TextDisplay::displayStatus() const {
    int sum_crit;
    for (int i = 0 ; i < 4 ; i++) {
        sum_crit = 0;
        for (auto &j : studentCriteria.at(i)) {
            sum_crit += j.at(1);
        }

        switch (i) {
            case 0: cout << Colour::Blue; break;
            case 1: cout << Colour::Red; break;
            case 2: cout << Colour::Orange; break;
            case 3: cout << Colour::Yellow; break;
        }

        cout << " has ";



        cout << sum_crit << " victory points, " << 
        studentResources.at(i).at(Resource::LUMBER) << " lumbers, " <<
        studentResources.at(i).at(Resource::WOOL) << " wools, " <<
        studentResources.at(i).at(Resource::GRAIN) << " grains, " <<
        studentResources.at(i).at(Resource::ORE) << " ores, and " <<
        studentResources.at(i).at(Resource::BRICK) << " bricks." << endl;
    }
}

void TextDisplay::displayCriteria() const {
    cout << curStudent << " has completed:" << endl;

    int index = -1;
    if (curStudent == Colour::Blue) {
        index = 0;
    } else if (curStudent == Colour::Red) {
        index = 1;
    } else if (curStudent == Colour::Orange) {
        index = 2;
    } else if (curStudent == Colour::Yellow) {
        index = 3;
    } else {
        throw std::runtime_error("Index not properly initalized");
    }

    for (auto &i : studentCriteria.at(index)) {
        cout << i.at(1) << " " << i.at(0) << endl;
    }

}

void TextDisplay::promptLoadedDice() const {
    cout << "Input a roll between 2 and 12:" << endl << "> ";
}

void TextDisplay::promptInitialSettlement() const {
    cout << "Student " << curStudent << ", where do you want to complete an Settlement?" << endl;
    cout << "Type \"complete <index>\" to choose a criterion or \"quit\" to quit:" << endl;
    cout << "> ";

}

void TextDisplay::displayStealChoices(vector<Colour> students) {
    cout << "Student " << curStudent << " can choose to steal from: ";

    sortColours(students);


    bool first = true;
    for (Colour c : students) {
        if (!first) {
            std::cout << ", ";  
        }
        cout << c;
        first = false;
    }
    cout << "." << endl;
    cout << "Choose a student to steal from." << endl << "> ";
}

void TextDisplay::promptTrade(detailedTrade deal) const {
    cout << curStudent << " offers " << deal.target << " one " << deal.offer <<
     " for one " << deal.want << endl;
    cout << "Does " << deal.target << " accept this offer?" << endl << "> ";
}

void TextDisplay::promptPlayAgain() const {
    cout << "Would you like to play again?" << endl << "> ";
}

void TextDisplay::displayHelp() const {
    cout << "Valid commands:" << endl;
    cout << "board" << endl;
    cout << "status" << endl << "criteria" << endl;
    cout << "achieve <road>" << endl;
    cout << "complete <criterion>" << endl;
    cout << "improve <criterion>" << endl;
    cout << "trade <colour> <give> <take>" << endl;
    cout << "next" << endl << "save <file>" << endl;
    cout << "help" << endl << "> ";
}

void TextDisplay::up(int& c, int& t, int& g) const {
    // Helper lambda to repeat a character n times
    auto repeat = [](char ch, int n) { return std::string(n, ch); };

    cout << repeat(' ', 35)
         << "|" << players[boardCriteria.at(c)] << boardCriteria.at(c) << reset
         << "|--" << convertLetter(boardRoads.at(g)) << "--|"
         << players[boardCriteria.at(c + 1)] << boardCriteria.at(c + 1) << reset << "|"
         << endl;
    c += 2;
    g++;

    cout << repeat(' ', 35) << "/" << repeat(' ', 12) << "\\" << endl;

    cout << repeat(' ', 33) << convertLetter(boardRoads.at(g)) << "       0     "
         << convertLetter(boardRoads.at(++g)) << endl;
    g++;

    cout << repeat(' ', 33) << "/" << "     " << colourMap[boardTiles[t]]
         << repeat(' ', 11 - boardTiles[t].size()) << "\\" << endl;
    t++;

    cout << repeat(' ', 20)
         << "|" << players[boardCriteria.at(c)] << boardCriteria.at(c) << reset
         << "|--" << convertLetter(boardRoads.at(g)) << "--|"
         << players[boardCriteria.at(c + 1)] << boardCriteria.at(c + 1) << reset << "|"
         << repeat(' ', 7) << boardProb.at(t - 1) << "       |"
         << players[boardCriteria.at(c + 2)] << boardCriteria.at(c + 2) << reset
         << "|--" << convertLetter(boardRoads.at(++g)) << "--|"
         << players[boardCriteria.at(c + 3)] << boardCriteria.at(c + 3) << reset << "|"
         << endl;
    c += 4;
    g++;

    cout << repeat(' ', 20) << "/" << repeat(' ', 12) << "\\"
         << "     " << (robberPos == t - 1 ? "ROBBER" : "     ")
         << "      /" << repeat(' ', 12) << "\\" << endl;

    cout << repeat(' ', 18) << convertLetter(boardRoads.at(g++)) << "      "
         << (t < 10 ? " " + std::to_string(t) : std::to_string(t)) << "     "
         << convertLetter(boardRoads.at(g++)) << "             "
         << convertLetter(boardRoads.at(g++)) << "      "
         << (t + 1 < 10 ? " " + std::to_string(t + 1) : std::to_string(t + 1)) << "     "
         << convertLetter(boardRoads.at(g)) << endl;
    g++;

    cout << repeat(' ', 18) << "/" << "     " << colourMap[boardTiles[t]]
         << repeat(' ', 11 - boardTiles[t].size()) << "\\" << repeat(' ', 12)
         << "/" << "     " << colourMap[boardTiles[++t]]
         << repeat(' ', 11 - boardTiles[t].size()) << "\\" << endl;
    t++;
}


void TextDisplay::down(int& c, int& t, int& g) const {
    // Helper lambda to repeat a character n times
    auto repeat = [](char ch, int n) { return std::string(n, ch); };

    // Initial spacing and loop for the first line
    cout << repeat(' ', 5);
    for (int i = 0; i < 2; ++i) {
        cout << "|" << players[boardCriteria.at(c)] << boardCriteria.at(c) << reset
             << "|--" << convertLetter(boardRoads.at(g)) << "--|"
             << players[boardCriteria.at(c + 1)] << boardCriteria.at(c + 1) << reset << "|";
        c += 2;
        g++;
        cout << "       " << boardProb.at(t - 2 + i) << "       ";
    }
    cout << "|" << players[boardCriteria.at(c)] << boardCriteria.at(c) << reset
         << "|--" << convertLetter(boardRoads.at(g)) << "--|"
         << players[boardCriteria.at(c + 1)] << boardCriteria.at(c + 1) << reset << "|";
    c += 2;
    g++;
    cout << endl;

    // Second line with robber positions
    cout << repeat(' ', 18)
         << "\\" << "     " << (robberPos == t - 2 ? "ROBBER" : "     ") << "      /"
         << repeat(' ', 12) << "\\     "
         << (robberPos == t - 1 ? "ROBBER" : "     ") << "      /" << endl;

    // Third line with Road letters and tile number
    cout << repeat(' ', 18)
         << convertLetter(boardRoads.at(g++)) << repeat(' ', 13)
         << convertLetter(boardRoads.at(g++)) << "      " << t << "     "
         << convertLetter(boardRoads.at(g++)) << repeat(' ', 13)
         << convertLetter(boardRoads.at(g++)) << endl;

    // Fourth line with tile names
    cout << repeat(' ', 20) << "\\" << repeat(' ', 12) << "/"
         << "     " << colourMap[boardTiles[t]]
         << repeat(' ', 11 - boardTiles[t].size()) << "\\"
         << repeat(' ', 12) << "/" << endl;
    t++;

    // Fifth line with probabilities and criteria
    cout << repeat(' ', 20)
         << "|" << players[boardCriteria.at(c)] << boardCriteria.at(c) << reset
         << "|--" << convertLetter(boardRoads.at(g)) << "--|"
         << players[boardCriteria.at(c + 1)] << boardCriteria.at(c + 1) << reset << "|";
    c += 2;
    g++;
    cout << repeat(' ', 7) << boardProb.at(t - 1) << "       |"
         << players[boardCriteria.at(c)] << boardCriteria.at(c) << reset
         << "|--" << convertLetter(boardRoads.at(g)) << "--|"
         << players[boardCriteria.at(c + 1)] << boardCriteria.at(c + 1) << reset << "|"
         << endl;
    c += 2;
    g++;

    // Sixth line with robber position
    cout << repeat(' ', 33) << "\\" << "     "
         << (robberPos == t - 1 ? "ROBBER" : "     ") << "      /" << endl;

    // Seventh line with Road letters
    cout << repeat(' ', 33) << convertLetter(boardRoads.at(g++))
         << repeat(' ', 13) << convertLetter(boardRoads.at(g++)) << endl;

    // Eighth line with slashes
    cout << repeat(' ', 35) << "\\" << repeat(' ', 12) << "/" << endl;

    // Final line with criteria
    cout << repeat(' ', 35)
         << "|" << players[boardCriteria.at(c)] << boardCriteria.at(c) << reset
         << "|--" << convertLetter(boardRoads.at(g)) << "--|"
         << players[boardCriteria.at(c + 1)] << boardCriteria.at(c + 1) << reset << "|"
         << endl;
    c += 2;
    g++;
}


void TextDisplay::middle(int& c, int& t, int& g) const {
    // Helper lambda to repeat a character n times
    auto repeat = [](char ch, int n) { return std::string(n, ch); };

    // First line with criteria and probabilities
    cout << repeat(' ', 5);
    for (int i = 0; i < 2; ++i) {
        cout << "|" << players[boardCriteria.at(c)] << boardCriteria.at(c) << reset
             << "|--" << convertLetter(boardRoads.at(g)) << "--|"
             << players[boardCriteria.at(c + 1)] << boardCriteria.at(c + 1) << reset << "|";
        c += 2;
        g++;
        cout << "       " << boardProb.at(t - 2 + i) << "       ";
    }
    cout << "|" << players[boardCriteria.at(c)] << boardCriteria.at(c) << reset
         << "|--" << convertLetter(boardRoads.at(g)) << "--|"
         << players[boardCriteria.at(c + 1)] << boardCriteria.at(c + 1) << reset << "|";
    c += 2;
    g++;
    cout << endl;

    // Second line with slashes and robber positions
    cout << repeat(' ', 5);
    for (int j = 0; j < 2; ++j) {
        cout << "/" << repeat(' ', 12) << "\\     "
             << (robberPos == t - 2 + j ? "ROBBER" : "     ") << "      ";
    }
    cout << "/" << repeat(' ', 12) << "\\" << endl;

    // Third line with Road letters and tile numbers
    cout << "   " << convertLetter(boardRoads.at(g++)) << "      "
         << (t < 10 ? " " + std::to_string(t) : std::to_string(t)) << "     "
         << convertLetter(boardRoads.at(g++)) << repeat(' ', 13)
         << convertLetter(boardRoads.at(g++)) << "      "
         << (t + 1 < 10 ? " " + std::to_string(t + 1) : std::to_string(t + 1)) << "     "
         << convertLetter(boardRoads.at(g++)) << repeat(' ', 13)
         << convertLetter(boardRoads.at(g++)) << "      "
         << (t + 2 < 10 ? " " + std::to_string(t + 2) : std::to_string(t + 2)) << "     "
         << convertLetter(boardRoads.at(g++)) << endl;

    // Fourth line with tile names
    cout << "   /     " << colourMap[boardTiles[t]]
         << repeat(' ', 11 - boardTiles[t].size()) << "\\";
    t++;
    cout << repeat(' ', 12) << "/     " << colourMap[boardTiles[t]]
         << repeat(' ', 11 - boardTiles[t].size()) << "\\";
    t++;
    cout << repeat(' ', 12) << "/     " << colourMap[boardTiles[t]]
         << repeat(' ', 11 - boardTiles[t].size()) << "\\" << endl;
    t++;

    // Fifth line with criteria and probabilities
    for (int i = 0; i < 2; ++i) {
        cout << "|" << players[boardCriteria.at(c++)] << boardCriteria.at(c - 1) << reset << "|"
             << "       " << boardProb.at(t - 3 + i) << "       |"
             << players[boardCriteria.at(c++)] << boardCriteria.at(c - 1) << reset
             << "|--" << convertLetter(boardRoads.at(g++)) << "--";
    }
    cout << "|" << players[boardCriteria.at(c++)] << boardCriteria.at(c - 1) << reset << "|"
         << "       " << boardProb.at(t - 1) << "       |"
         << players[boardCriteria.at(c++)] << boardCriteria.at(c - 1) << reset << "|" << endl;

    // Sixth line with slashes and robber positions
    cout << "   \\" << "     " << (robberPos == t - 3 ? "ROBBER" : "     ") << "      /"
         << repeat(' ', 12) << "\\" << "     "
         << (robberPos == t - 2 ? "ROBBER" : "     ") << "      /"
         << repeat(' ', 12) << "\\" << "     "
         << (robberPos == t - 1 ? "ROBBER" : "     ") << "      /" << repeat(' ', 12) << endl;

    // Seventh line with Road letters and tile numbers
    cout << "   " << convertLetter(boardRoads.at(g++)) << repeat(' ', 13)
         << convertLetter(boardRoads.at(g++)) << "      "
         << (t < 10 ? " " + std::to_string(t) : std::to_string(t)) << "     "
         << convertLetter(boardRoads.at(g++)) << repeat(' ', 13)
         << convertLetter(boardRoads.at(g++)) << "      "
         << (t + 1 < 10 ? " " + std::to_string(t + 1) : std::to_string(t + 1)) << "     "
         << convertLetter(boardRoads.at(g++)) << repeat(' ', 13)
         << convertLetter(boardRoads.at(g++)) << endl;

    // Eighth line with backslashes and tile names
    cout << repeat(' ', 5);
    for (int j = 0; j < 2; ++j) {
        cout << "\\" << repeat(' ', 12) << "/" << "     " << colourMap[boardTiles[t]]
             << repeat(' ', 11 - boardTiles[t].size());
        t++;
    }
    cout << "\\" << repeat(' ', 12) << "/" << endl;
}


void TextDisplay::displayBoard() const{
    int crit_cout = 0, tile_count = 0, road_count = 0;
    up(crit_cout, tile_count, road_count);
    middle(crit_cout, tile_count, road_count);
    middle(crit_cout, tile_count, road_count);
    middle(crit_cout, tile_count, road_count);
    down(crit_cout, tile_count, road_count);
}

void TextDisplay::displayGainedResource(const map<Resource, int> resources,
const Colour student) const {
    cout << "Student " << student << " gained:" << endl;
    for (auto &r : resources) {
        cout << r.second << " " << r.first << endl;
    }
    cout << "> ";
}




void TextDisplay::notify(Subject<WatanState> &whoFrom) {
    curStudent = whoFrom.getState().curTurn;
}

void TextDisplay::notify(Subject<StudentState> &whoFrom) {
    int index = -1;
    if (whoFrom.getState().appliedTo == Colour::Blue) {
        index = 0;
    } else if (whoFrom.getState().appliedTo == Colour::Red) {
        index = 1;
    } else if (whoFrom.getState().appliedTo == Colour::Orange) {
        index = 2;
    } else if (whoFrom.getState().appliedTo == Colour::Yellow) {
        index = 3;
    } else {
        throw std::runtime_error("Index not properly initalized");
    }

    for (auto &r: whoFrom.getState().resourceChange) {
        studentResources.at(index).at(r.first) += r.second;
    }
}

void TextDisplay::notify(Subject<CriterionState> &whoFrom) {
    int index = -1;
    int crit_index = -1;
    string player, crit;
    if (whoFrom.getState().newOwner == Colour::Blue) {
        index = 0;
        player = 'B';
    } else if (whoFrom.getState().newOwner == Colour::Red) {
        index = 1;
        player = 'R';
    } else if (whoFrom.getState().newOwner == Colour::Orange) {
        index = 2;
        player = 'O';
    } else if (whoFrom.getState().newOwner == Colour::Yellow) {
        index = 3;
        player = 'Y';
    } else {
        throw std::runtime_error("Index not properly initalized");
    }


    if (whoFrom.getState().newTier == CritType::Settlement) {
        crit_index = 1;
        crit = 'S';
    } else if (whoFrom.getState().newTier == CritType::City) {
        crit_index = 2;
        crit = 'C';
    } else if (whoFrom.getState().newTier == CritType::Exam) {
        crit_index = 3;
        crit = 'E';
    } else {
        throw std::runtime_error("Crit Index not properly initalized");
    }




    if (studentCriteria.at(index).size() != 0 && studentCriteria.at(index).at(studentCriteria.at(index).size() - 1).at(0)
     == crit_index) {
        studentCriteria.at(index).at(studentCriteria.at(index).size() - 1).at(1)++;
    } else {
        studentCriteria.at(index).push_back({crit_index, 1});
    }

    boardCriteria.at(whoFrom.getState().index) = player + crit;
}

void TextDisplay::notify(Subject<TileState> &whoFrom) {
    if (whoFrom.getState().hasRobber) {
        robberPos = whoFrom.getState().index;
    }
}

void TextDisplay::notify(Subject<RoadState> &whoFrom) {
    string player;
    switch(whoFrom.getState().newOwner) {
        case Colour::Blue: player = 'B'; break;
        case Colour::Red: player = 'R'; break;
        case Colour::Orange: player = 'O'; break;
        case Colour::Yellow: player = 'Y'; break;
        case Colour::NoColour: break;
    }
    boardRoads.at(whoFrom.getState().index) = player + " ";
}

void TextDisplay::notify(Subject<DiceState> &whoFrom) {
    int value = whoFrom.getState().diceVal;
    cout << "Dice rolled: " << value << "." << endl;
}
