#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <string>
#include <deque>      // Use deque for message storage optimization
#include <cstdint>    // For uint32_t

// Enum declarations
enum class Game_State {
    Playing,
    Paused
};

enum class Game_Rule : uint32_t {
    ShowVision       = 1 << 0,  // 1
    NoVision         = 1 << 1,  // 2
    VariableVelocity = 1 << 2,  // 4
    FixedVelocity    = 1 << 3,  // 8
    SetAngle         = 1 << 4,  // 16
    VariableAngle    = 1 << 5,  // 32
    BoidCohesion     = 1 << 6,  // 64
    NoCohesion       = 1 << 7,  // 128
    BoidSeparation   = 1 << 8,  // 256
    NoSeparation     = 1 << 9   // 512
};

enum class Obstacle_Mode {
    Place,
    Remove
};

enum class Message_Category {
    Input,
    Timed, 
    System,
    Debug
};

// Message structure
struct Message {
    Message(const std::string& msgText, float lifetime, Message_Category msgCategory, sf::Vector2f pos, bool isCenter);

    std::string text;           // The content of the message
    Message_Category category;  // The type of message (e.g., Input, Timed, System)
    float duration;             // How long the message stays on the screen (0 = infinite)
    sf::Clock timer;            // Tracks how long the message has been active
    sf::Vector2f position;      // Position on the screen (if not centered)
    bool center;                // Whether the message should be centered on the screen
};

// Game_Manager class
class Game_Manager {
public:
    Game_Manager();  // Constructor
    
    // Font handling
    bool loadFont(const std::string& fontPath);  // Load a font from a file
    const sf::Font& getFont() const;            // Access the loaded font

    // Game state management
    void setState(Game_State state);  // Set the current game state
    Game_State getState() const;      // Get the current game state
    bool isPaused() const;            // Check if the game is paused

    // Game rule management
    void enableRule(Game_Rule rule);    // Enable a specific game rule
    void disableRule(Game_Rule rule);   // Disable a specific game rule
    bool isRuleEnabled(Game_Rule rule) const; // Check if a rule is enabled

    // Obstacle mode management
    void setMode(Obstacle_Mode mode);  // Set obstacle mode (Place/Remove)
    Obstacle_Mode getMode() const;     // Get the current obstacle mode
    bool isPlacing() const;            // Check if the mode is set to "Place"

    // Message handling
    void addMessage(const std::string& inText, float lifetime, Message_Category category, sf::Vector2f position); // Add a new message
    const std::deque<Message>& getMessages() const;  // Access the list of messages (changed to deque for better performance)
    bool isMessage() const;            // Check if there are any active messages
    void cleanCategory(Message_Category category);    // Remove all messages of a specific category

private:
    sf::Font font;                   // Font for rendering text
    Game_State Current_State;        // Current game state
    uint32_t activeRules = 0;        // Bitmask for active game rules
    Obstacle_Mode Current_Obstacle_Mode;  // Current obstacle mode (Place/Remove)
    std::deque<Message> messages;   // Changed to deque for better performance with insertions/removals

    uint32_t toMask(Game_Rule rule) const; // Helper function for bitmask conversion
};
