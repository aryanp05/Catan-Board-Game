# Catan Board Game - C++ Implementation 🎲

Welcome to the **Catan Board Game** project! 🚀 This repository features two implementations of the classic Catan board game, crafted in **C++** with a focus on **object-oriented programming** (OOP).

- **Version 1**: 🏫 *Students of Watan* - A University of Waterloo-inspired variant, developed for a CS246 assignment.
- **Version 2**: 🌍 *Original Catan* - A faithful recreation of the original Catan board game with standard rules and resources.

---

## 📚 Table of Contents

1. [✨ Features](#-features)
2. [📜 Gameplay Rules](#-gameplay-rules)
3. [🛠️ Setup Instructions](#%EF%B8%8F-setup-instructions)
4. [🎮 How to Play](#-how-to-play)
5. [🔍 Design Patterns Used](#-design-patterns-used)
6. [🌟 Future Improvements](#-future-improvements)

---

## ✨ Features

### Version 1: Students of Watan 🏫
- **Custom Resources**: 
  - `CAFFEINE ☕`, `LECTURE 📘`, `LAB 🧪`, `TUTORIAL 🎓`, and `STUDY 📖`.
- **Unique Rules**: Includes geese mechanics 🪿, course criteria, and achievements.
- **Turn-Based Gameplay**: 🎲 Supports 4 players with alternating turns.
- **Dice Customization**: Choose between `fair dice` 🎲 (random rolls) or `loaded dice` 🎯 (user-defined rolls).
- **File Management**: Save and load game states for continuity 📂.

### Version 2: Original Catan 🌍
- **Standard Resources**: 
  - `Brick 🧱`, `Lumber 🌲`, `Grain 🌾`, `Ore ⛏️`, and `Wool 🐑`.
- **Classic Gameplay**: Follows the traditional Settlers of Catan rules 🛤️.
- **Resource Trading**: Propose trades to other players for strategic gains 💱.
- **Victory Points System**: First player to reach `10 points` 🏆 wins!

---

## 📜 Gameplay Rules

### General 🎯
- Both versions follow turn-based gameplay.
- Players gather resources based on dice rolls 🎲 and their settlements' locations.
- Victory is achieved by earning **10 points** through strategic decisions 🏅.

### Version 1: Students of Watan 🏫
- Unique resource tiles tailored to the custom theme.
- Geese mechanic 🪿 disrupts resource collection on targeted tiles.
- Criteria completion simulates academic progression (Assignment → Midterm → Exam).

### Version 2: Original Catan 🌍
- Standard resource tiles with classic distribution.
- Settlements, cities, and roads drive strategy and scoring 🏘️.

---

## 🛠️ Setup Instructions

### Prerequisites 📋
- A **C++ compiler** (e.g., `g++`, `clang++`).
- Basic knowledge of command-line operations 💻.

### Build and Run 🚀
1. **Clone the repository**:
   ```bash
   git clone https://github.com/yourusername/catan-board-game.git
   cd catan-board-game
   ```
2. **Compile the desired version**:
   ```bash
   g++ -o watan students_of_watan.cpp
   g++ -o catan original_catan.cpp
   ```
3. **Run the game**:
   ```bash
   ./watan   # For Students of Watan
   ./catan   # For Original Catan
   ```

---

## 🎮 How to Play

1. Follow the on-screen prompts to set up your game board 🗺️.
2. Take turns rolling dice, collecting resources, and making strategic decisions 🎲.
3. Save your progress anytime and reload it to continue where you left off 💾.

---

## 🔍 Design Patterns Used

- **Factory Pattern** 🏭: For generating game components like tiles and resources.
- **Strategy Pattern** 🧠: Allows dynamic switching between `fair` and `loaded` dice.
- **Observer Pattern** 👁️: Tracks changes in player states and updates the game board.
- **Command Pattern** 💻: Handles player actions (e.g., trading, building, saving).

---

## 🌟 Future Improvements

- Add a **graphical user interface (GUI)** for enhanced user interaction 🖥️.
- Incorporate **AI players** 🤖 with varying difficulty levels.
- Expand board customization options (e.g., hex size, alternate layouts) 🎨.

---

Feel free to fork the repository, submit issues, or create pull requests! 🚀 Let the games begin!

---

## 🏆 Contributors

Made with ❤️ by Aryan Patel and the spirit of strategic board gaming!
