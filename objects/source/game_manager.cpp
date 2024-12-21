#include "../header/game_manager.h"
#include <algorithm> // For std::remove_if
#include <unordered_set>  // For quick duplicate checking

Message::Message(const std::string& msgText, float lifetime, Message_Category msgCategory, sf::Vector2f pos, bool isCenter)
    : text(msgText),
      category(msgCategory),
      duration(lifetime),
      position(pos),
      center(isCenter) {
    timer.restart(); // Start the timer to track the message's lifetime
}


// Constants and Initializations
const uint32_t allRulesMask = (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4) | 
                              (1 << 5) | (1 << 6) | (1 << 7) | (1 << 8) | (1 << 9);

// Constructor: Initialize the game state to "Playing"
Game_Manager::Game_Manager() 
    : Current_State(Game_State::Playing),
      activeRules(allRulesMask),
      Current_Obstacle_Mode(Obstacle_Mode::Place) {
}

// Load font from a specified path
bool Game_Manager::loadFont(const std::string& fontPath) {
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Error: Failed to load font in Game_Manager from: " << fontPath << std::endl;
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
    activeRules |= toMask(rule); // Set the corresponding bit
}

// Disable a specific game rule
void Game_Manager::disableRule(Game_Rule rule) {
    activeRules &= ~toMask(rule); // Clear the corresponding bit
}

// Check if a specific game rule is enabled
bool Game_Manager::isRuleEnabled(Game_Rule rule) const {
    return activeRules & toMask(rule); // Check if the corresponding bit is set
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

// Clean messages of a certain category
void Game_Manager::cleanCategory(Message_Category category) {
    messages.erase(
        std::remove_if(messages.begin(), messages.end(),
            [category](const Message& msg) { return msg.category == category; }
        ),
        messages.end()
    );
}


void Game_Manager::addMessage(const std::string& inText, float lifetime, Message_Category category, sf::Vector2f position) {
    // Ensure the input category is clean before adding
    if (category == Message_Category::Input) {
        cleanCategory(Message_Category::Input);  // Clear previous input messages
    }

    // Avoid duplicates: Check if this message already exists
    auto it = std::find_if(messages.begin(), messages.end(),
        [&](const Message& msg) { return msg.text == inText && msg.category == category; });

    if (it == messages.end()) {  // Only add if it's not already there
        Message newMessage(inText, lifetime, category, position, true);
        messages.push_back(newMessage);  // Insert at the back of deque
    }
}


// Get the list of messages
const std::deque<Message>& Game_Manager::getMessages() const {
    return messages;  // Return a reference to the deque
}


// Check if there are any messages
bool Game_Manager::isMessage() const {
    return !messages.empty();
}
