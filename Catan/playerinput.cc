#include <iostream>
#include <fstream>
#include "playerinput.h"
#include "state.h"

using namespace std;

// Function to get the file name for saving the game state
string PlayerInput::getSaveFile() {
    string input;

    // Prompt the user to input the save file name
    cin >> input;

    return input;
}

// Function to save the game state to a specified file
void PlayerInput::saveGameState(const string& filename) {
    // Open the file to save the game state
    ofstream backupFile(filename);

    // Check if the file was successfully opened
    if (backupFile.is_open()) {
        // Write a placeholder message for the saved state
        backupFile << "Game state saved." << endl << "> ";
        backupFile.close();  // Close the file after writing
    }
}

// Function to get the trade details (resources and colour)
detailedTrade PlayerInput::getTrade() {
    string input;
    Resource r_1, r_2;
    Colour c;

    // Continuously prompt the user for a valid trade input
    while (true) {
        // Read and validate Colour
        cin >> input;
        if (input == "Blue" || input == "blue") c = Colour::Blue;
        else if (input == "Red" || input == "red") c = Colour::Red;
        else if (input == "Orange" || input == "orange") c = Colour::Orange;
        else if (input == "Yellow" || input == "yellow") c = Colour::Yellow;
        else {
            // If Colour is invalid, display error and restart loop
            cout << "Invalid colour. Try again." << endl;
            return detailedTrade{Colour::NoColour, Resource::DESERT, Resource::DESERT};
        }

        // Read and validate the first resource
        cin >> input;
        if (input == "BRICK" || input == "brick") r_1 = Resource::BRICK;
        else if (input == "GRAIN" || input == "grain") r_1 = Resource::GRAIN;
        else if (input == "ORE" || input == "ore") r_1 = Resource::ORE;
        else if (input == "LUMBER" || input == "lumber") r_1 = Resource::LUMBER;
        else if (input == "WOOL" || input == "wool") r_1 = Resource::WOOL;
        else {
            // If first resource is invalid, display error and restart loop
            cout << "Invalid resource offer. Try again." << endl;
            return detailedTrade{Colour::NoColour, Resource::DESERT, Resource::DESERT};
        }

        // Read and validate the second resource
        cin >> input;
        if (input == "BRICK" || input == "brick") r_2 = Resource::BRICK;
        else if (input == "GRAIN" || input == "grain") r_2 = Resource::GRAIN;
        else if (input == "ORE" || input == "ore") r_2 = Resource::ORE;
        else if (input == "LUMBER" || input == "lumber") r_2 = Resource::LUMBER;
        else if (input == "WOOL" || input == "wool") r_2 = Resource::WOOL;
        else {
            // If second resource is invalid, display error and restart loop
            cout << "Invalid resource request. Try again." << endl;
            return detailedTrade{Colour::NoColour, Resource::DESERT, Resource::DESERT};
        }

        // All inputs are valid, break the loop
        break;
    }

    // Return the validated trade details
    return detailedTrade{c, r_1, r_2};
}

// Function to get a Yes/No response from the player
Response PlayerInput::getResponse() {
    string input;

    // Continuously prompt for a valid Yes/No response
    while (true) {
        cin >> input;

        // Check if the input is Yes or No
        if (input == "Yes" || input == "yes") return Response::Yes;
        else if (input == "No" || input == "no") return Response::No;

        // Clear invalid input and prompt again
        cin.clear();
        cin.ignore(1, '\n');
        cout << "Invalid command. " << endl << "> "; 

        // If end of input stream (EOF), save game state and return Yes
        if (cin.eof()) {
            saveGameState("backup.sv");
            return Response::Yes;
        }
    }
}

// Function to get the player's command input
Command PlayerInput::getCommand() {
    string command;

    // Continuously prompt the user for a command
    while (true) {
        cin >> command;

        // Check for valid commands and return corresponding Command
        if (command == "board") return Command::Board;
        else if (command == "status") return Command::Status;
        else if (command == "roll") return Command::Roll;
        else if (command == "criteria") return Command::Criteria;
        else if (command == "achieve") return Command::Achieve;
        else if (command == "complete") return Command::Complete;
        else if (command == "improve") return Command::Improve;
        else if (command == "trade") return Command::Trade;
        else if (command == "next") return Command::Next;
        else if (command == "save") return Command::Save;
        else if (command == "help") return Command::Help;
        else if (command == "load") return Command::DiceLoad;
        else if (command == "fair") return Command::DiceFair;
        else if (command == "quit") return Command::Quit;

        // If command is invalid, display error and prompt again
        if (cin.eof()) {
            saveGameState("backup.sv");
            cout << "Game ended. State saved to backup.sv.\n";
            exit(0);  // Exit the game
        }

        // Clear invalid input and prompt again
        cin.ignore(1, '\n');
        cout << "Invalid command." << endl << "> ";
    }
}

// Function to get a valid loaded dice roll within a specified range
int PlayerInput::getLoadedDice(const int min, const int max) {
    int value;

    // Continuously prompt the user for a valid dice roll
    while (true) {
        if (cin >> value) {
            // Check if the value is within the allowed range
            if (value >= min && value <= max) {
                return value;
            } else {
                cout << "Invalid roll." << endl << "> ";
            }
        } else {
            // Clear input errors and try again
            cin.clear();
            cin.ignore(1, '\n');
        }
    }
}

// Function to get a valid criterion placement within a specified range
int PlayerInput::getCriterionPlacement(const int min, const int max) {
    int index;

    // Continuously prompt for a valid index
    while (true) {
        if (cin >> index) {
            if (index >= min && index <= max) return index;
        } else {
            // Clear input errors and try again
            cin.clear();
            cin.ignore(1, '\n');
        }
    }
}

// Function to get a valid Road placement within a specified range
int PlayerInput::getRoadPlacement(const int min, const int max) {
    int index;

    // Continuously prompt for a valid index
    while (true) {
        if (cin >> index) {
            if (index >= min && index <= max) return index;
        } else {
            // Clear input errors and try again
            cin.clear();
            cin.ignore(1, '\n');
        }
    }
}

// Function to get a valid tile index within a specified range
int PlayerInput::getTile(const int min, const int max) {
    int index;

    // Continuously prompt for a valid index
    while (true) {
        if (cin >> index) {
            if (index >= min && index <= max) return index;
        } else {
            // Clear input errors and try again
            cin.clear();
            cin.ignore(1, '\n');
        }
    }
}

// Function to get a valid steal choice from the player
Colour PlayerInput::getStealChoice(const vector<Colour>& choices) {
    string input;
    Colour c;

    // Continuously prompt for a valid steal choice
    while (true) {
        cin >> input;

        // Check for valid Colour input
        if (input == "Blue" || input == "blue") c = Colour::Blue;
        else if (input == "Red" || input == "red") c = Colour::Red;
        else if (input == "Orange" || input == "orange") c = Colour::Orange;
        else if (input == "Yellow" || input == "yellow") c = Colour::Yellow;
        else {
            // Skip invalid input and prompt again
            getline(cin, input); 
            continue;
        }

        // Check if the chosen colour is in the list of valid choices
        for (Colour cl : choices) {
            if (cl == c) return c;
        }

        // If invalid, prompt again
        cout << "Invalid choice." << endl << "> ";
    }
}
