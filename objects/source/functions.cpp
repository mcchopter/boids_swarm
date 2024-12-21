// functions.cpp
#include "../header/functions.h"

void handleGameRuleEvent(sf::Keyboard::Key key, Game_Manager& gameStateManager) {
    if (key == sf::Keyboard::V) {
        toggleRule(gameStateManager, Game_Rule::ShowVision, "ShowVision");
    }
    else if (key == sf::Keyboard::C) {
        toggleRule(gameStateManager, Game_Rule::BoidCohesion, "Boid Cohesion");
    }
    else if (key == sf::Keyboard::S) {
        toggleRule(gameStateManager, Game_Rule::BoidSeparation, "Boid Separation");
    }
    else if (key == sf::Keyboard::A) {
        toggleRule(gameStateManager, Game_Rule::VariableAngle, "Variable Angle");
    }
    else if (key == sf::Keyboard::Z) {
        toggleRule(gameStateManager, Game_Rule::VariableVelocity, "Variable Velocity");
    }
}

void processEvent(sf::Event& event, Game_Manager& gameStateManager) {
    // Only handle events if not paused
    if (!gameStateManager.isPaused()) {
        if (event.type == sf::Event::KeyPressed) {
            handleGameRuleEvent(event.key.code, gameStateManager);
            if (event.key.code == sf::Keyboard::D) {
                toggleObstacleMode(gameStateManager);
            }
        }
    }
    
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
        togglePause(gameStateManager);
    }
}
