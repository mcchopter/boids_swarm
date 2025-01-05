#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "../header/functions.h"
#include "../header/boid.h"
#include <cmath>
#include <vector>
#include <iostream>


// Handle game rule toggling via keyboard
void handleGameRuleEvent(sf::Keyboard::Key key, Game_Manager& gameStateManager) {
    if (key == sf::Keyboard::V) {
        toggleRule(gameStateManager, Game_Rule::ShowVision, "ShowVision");
    } else if (key == sf::Keyboard::C) {
        toggleRule(gameStateManager, Game_Rule::BoidCohesion, "Boid Cohesion");
    } else if (key == sf::Keyboard::S) {
        toggleRule(gameStateManager, Game_Rule::BoidSeparation, "Boid Separation");
    } else if (key == sf::Keyboard::A) {
        toggleRule(gameStateManager, Game_Rule::VariableAngle, "Variable Angle");
    } else if (key == sf::Keyboard::Z) {
        toggleRule(gameStateManager, Game_Rule::VariableVelocity, "Variable Velocity");
    }
}

// Main event processing
void processEvent(sf::Event& event, Game_Manager& gameStateManager, sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::P) {
            // Toggle pause state
            togglePause(gameStateManager);
        } else if (!gameStateManager.isPaused()) {
            // Handle game rule events when game isn't paused
            handleGameRuleEvent(event.key.code, gameStateManager);
        }
    }

    if (!gameStateManager.isPaused()) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                std::cout << "Left mouse button pressed" << std::endl;

                // Get mouse position relative to the window
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mouseWorldPos = window.mapPixelToCoords(mousePos);

                // Spawn a boid at the mouse position, ensuring it does not overlap with others
                spawnBoid(gameStateManager, mouseWorldPos.x, mouseWorldPos.y, 20.0f); // Min distance 20 pixels

                // Optionally, rotate boids toward the mouse position
                for (auto& boid : gameStateManager.getBoids()) {
                    float dx = mouseWorldPos.x - boid.getX();
                    float dy = mouseWorldPos.y - boid.getY();
                    float angleRadians = std::atan2(dy, dx);
                    float angleDegrees = angleRadians * 180.f / M_PI;

                    boid.setTargetTurnAngle(angleDegrees);
                }
            }
        }
    }
}
