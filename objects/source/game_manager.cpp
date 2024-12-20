#include "../header/game_manager.h"

const uint32_t allRulesMask = (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7) | (1 << 8) | (1 << 9);

// Constructor: Initialize the game state to "Playing"
Game_Manager::Game_Manager() : Current_State(Game_State::Playing),
                                activeRules(allRulesMask),
                                Current_Obstacle_Mode(Obstacle_Mode::Place) {}

// Load font from a specified path
bool Game_Manager::loadFont(const std::string& fontPath) {
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Error: Font not loaded in Game_Manager!" << std::endl;
        return false;
    }
    std::cout << "Font successfully loaded in Game_Manager from: " << fontPath << std::endl;
    return true;
}

// Get the font used for rendering text
const sf::Font& Game_Manager::getFont() const {
    return font;
}

// Change the current game state (Playing/Paused)
void Game_Manager::setState(Game_State state) {
    Current_State = state;
}

// Retrieve the current game state
Game_State Game_Manager::getState() const {
    return Current_State;
}

// Check if the game is paused
bool Game_Manager::isPaused() const {
    return Current_State == Game_State::Paused;
}

// Enable a specific game rule
void Game_Manager::enableRule(Game_Rule rule) {
    activeRules |= toMask(rule);  // Use bitwise OR to set the bit
}

// Disable a specific game rule
void Game_Manager::disableRule(Game_Rule rule) {
    activeRules &= ~toMask(rule);  // Use bitwise AND and NOT to clear the bit
}

// Check if a specific game rule is enabled
bool Game_Manager::isRuleEnabled(Game_Rule rule) {
    return activeRules & toMask(rule);  // Use bitwise AND to check if the bit is set
}

// Set the current obstacle mode (Placing or Removing)
void Game_Manager::setMode(Obstacle_Mode mode) {
    Current_Obstacle_Mode = mode;
}

// Get the current obstacle mode
Obstacle_Mode Game_Manager::getMode() const {
    return Current_Obstacle_Mode;
}

// Check if the game is in the "Placing" state
bool Game_Manager::isPlacing() const {
    return Current_Obstacle_Mode == Obstacle_Mode::Place;
}

// Convert a Game_Rule enum to its corresponding bitmask value
uint32_t Game_Manager::toMask(Game_Rule rule) const {
    return static_cast<uint32_t>(rule);
}
