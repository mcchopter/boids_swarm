#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "game_manager.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

// Helper function to check and adjust position to avoid overlapping boids
inline void adjustPositionIfNeeded(float& x, float& y, const std::vector<Boid>& boids, float minDistance) {
    for (const auto& boid : boids) {
        float dx = x - boid.getX();
        float dy = y - boid.getY();
        float distanceSquared = dx * dx + dy * dy;

        if (distanceSquared < minDistance * minDistance) {
            float distance = std::sqrt(distanceSquared);
            float offset = (minDistance - distance) + 2.0f; // Ensure no overlap with margin
            x += offset * (dx / distance); // Adjust x
            y += offset * (dy / distance); // Adjust y
        }
    }
}

// Spawn a boid and ensure no overlap with existing boids
inline void spawnBoid(Game_Manager& gameStateManager, float startX, float startY, float minDistance = 20.0f) {
    auto& boids = gameStateManager.getBoids();
    adjustPositionIfNeeded(startX, startY, boids, minDistance);
    boids.emplace_back(startX, startY, 50.0f, 10.0f, 0.0f); // Example parameters for the new boid
}

// Handle game rule toggling via keyboard
inline void toggleRule(Game_Manager& gameStateManager, Game_Rule rule, const std::string& ruleName) {
    if (gameStateManager.isRuleEnabled(rule)) {
        gameStateManager.disableRule(rule);
        std::cout << ruleName << " is disabled!" << std::endl;
        gameStateManager.addMessage(ruleName + " is disabled!", 3.0f, Message_Category::Input, sf::Vector2f(100, 100));  // Example position
    } else {
        gameStateManager.enableRule(rule);
        std::cout << ruleName << " is enabled!" << std::endl;
        gameStateManager.addMessage(ruleName + " is enabled!", 3.0f, Message_Category::Input, sf::Vector2f(100, 100)); 
    }
}

// Toggle obstacle placement or removal mode
inline void toggleObstacleMode(Game_Manager& gameStateManager) {
    // Only toggle mode if state has changed
    Obstacle_Mode newMode = gameStateManager.isPlacing() ? Obstacle_Mode::Remove : Obstacle_Mode::Place;
    gameStateManager.setMode(newMode);
    
    std::string modeMessage = (newMode == Obstacle_Mode::Remove) ? "Obstacle mode set to Remove!" : "Obstacle mode set to Place!";
    std::cout << modeMessage << std::endl;
    gameStateManager.addMessage(modeMessage, 3.0f, Message_Category::Input, sf::Vector2f(100, 100));
}

// Pause the game or resume it
inline void togglePause(Game_Manager& gameStateManager) {
    // Consolidate toggle pause functionality
    Game_State newState = gameStateManager.isPaused() ? Game_State::Playing : Game_State::Paused;
    gameStateManager.setState(newState);
    
    std::string stateMessage = (newState == Game_State::Playing) ? "Game resumed!" : "Game paused!";
    std::cout << stateMessage << std::endl;
    gameStateManager.addMessage(stateMessage, 3.0f, Message_Category::Input, sf::Vector2f(100, 100));
}

// Handle game rule events based on key input
void handleGameRuleEvent(sf::Keyboard::Key key, Game_Manager& gameStateManager);

// Process events such as key presses or mouse clicks
void processEvent(sf::Event& event, Game_Manager& gameStateManager, sf::RenderWindow& window);

#endif
