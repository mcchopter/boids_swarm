#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>

enum class Game_State {
    Playing,
    Paused
};

enum class Game_Rule : uint32_t {
    ShowVision      = 1 << 0,  // 1
    NoVision        = 1 << 1,  // 2
    VariableVelocity = 1 << 2, // 4
    FixedVelocity   = 1 << 3,  // 8
    SetAngle        = 1 << 4,  // 16
    VariableAngle   = 1 << 5,  // 32
    BoidCohesion    = 1 << 6,  // 64
    NoCohesion      = 1 << 7,  // 128
    BoidSeparation  = 1 << 8,  // 256
    NoSeparation    = 1 << 9   // 512
};

enum class Obstacle_Mode {
    Place,
    Remove
};

struct TimedMessage {
    // Placeholder for future message handling
    sf::Text text;
    float timeToLive;
    std::string category;  // "input" or "notification", etc.
};

class Game_Manager {
public:
    Game_Manager();             // Constructor
    bool loadFont(const std::string& fontPath);
    const sf::Font& getFont() const;

    void setState(Game_State state); // Set the current game state
    Game_State getState() const;     // Get the current game state
    bool isPaused() const;          // Check if the game is paused

    // Methods to manipulate game rules
    void enableRule(Game_Rule rule);    // Enable a specific game rule
    void disableRule(Game_Rule rule);   // Disable a specific game rule
    bool isRuleEnabled(Game_Rule rule); // Check if a rule is enabled

    void setMode(Obstacle_Mode mode); // Set Right Click
    Obstacle_Mode getMode() const;    // Get Right Click state
    bool isPlacing() const;           // Check if Right Click is in Placing State

    // Future message handling: TimedMessage system is placeholder for now
    // const std::vector<TimedMessage>& getMessages() const;

private:
    sf::Font font;
    Game_State Current_State;
    uint32_t activeRules;
    Obstacle_Mode Current_Obstacle_Mode;
    // std::vector<TimedMessage> messages;  // Message system temporarily removed
    uint32_t toMask(Game_Rule rule) const; // Helper for bitmask conversion
};
