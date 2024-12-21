#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "game_manager.h"
#include <SFML/Graphics.hpp>

inline void toggleRule(Game_Manager& gameStateManager, Game_Rule rule, const std::string& ruleName) {
    if (gameStateManager.isRuleEnabled(rule)) {
        gameStateManager.disableRule(rule);
        std::cout << ruleName << " is disabled!" << std::endl;
        gameStateManager.addMessage(ruleName + " is disabled!", 3.0f, Message_Category::System, sf::Vector2f(100, 100));  // Example position
    } else {
        gameStateManager.enableRule(rule);
        std::cout << ruleName << " is enabled!" << std::endl;
        gameStateManager.addMessage(ruleName + " is enabled!", 3.0f, Message_Category::System, sf::Vector2f(100, 100)); 
        gameStateManager.addMessage(ruleName + " is enabled!", 3.0f, Message_Category::System, sf::Vector2f(100, 100));  // Example position
    }
}

inline void toggleObstacleMode(Game_Manager& gameStateManager) {
    // Only toggle mode if state has changed
    Obstacle_Mode newMode = gameStateManager.isPlacing() ? Obstacle_Mode::Remove : Obstacle_Mode::Place;
    gameStateManager.setMode(newMode);
    
    std::string modeMessage = (newMode == Obstacle_Mode::Remove) ? "Obstacle mode set to Remove!" : "Obstacle mode set to Place!";
    std::cout << modeMessage << std::endl;
    gameStateManager.addMessage(modeMessage, 3.0f, Message_Category::System, sf::Vector2f(100, 100));
}

inline void togglePause(Game_Manager& gameStateManager) {
    // Consolidate toggle pause functionality
    Game_State newState = gameStateManager.isPaused() ? Game_State::Playing : Game_State::Paused;
    gameStateManager.setState(newState);
    
    std::string stateMessage = (newState == Game_State::Playing) ? "Game resumed!" : "Game paused!";
    std::cout << stateMessage << std::endl;
    gameStateManager.addMessage(stateMessage, 3.0f, Message_Category::System, sf::Vector2f(100, 100));
}

void handleGameRuleEvent(sf::Keyboard::Key key, Game_Manager& gameStateManager);

void processEvent(sf::Event& event, Game_Manager& gameStateManager);

#endif
