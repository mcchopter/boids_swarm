#include "../header/functions.h"

void toggleRule(Game_Manager& gameStateManager, Game_Rule rule, const std::string& ruleName) {
    if (gameStateManager.isRuleEnabled(rule)) {
        gameStateManager.disableRule(rule);
        std::cout << ruleName << " is disabled!" << std::endl;
    } else {
        gameStateManager.enableRule(rule);
        std::cout << ruleName << " is enabled!" << std::endl;
    }
}

void toggleObstacleMode(Game_Manager& gameStateManager) {
    if (gameStateManager.isPlacing()) {
        gameStateManager.setMode(Obstacle_Mode::Remove);
        std::cout << "Obstacle mode set to Remove!" << std::endl;
    } else {
        gameStateManager.setMode(Obstacle_Mode::Place);
        std::cout << "Obstacle mode set to Place!" << std::endl;
    }
}

void togglePause(Game_Manager& gameStateManager) {
    if (gameStateManager.isPaused()) {
        gameStateManager.setState(Game_State::Playing);
        std::cout << "Game resumed!" << std::endl;
    } else {
        gameStateManager.setState(Game_State::Paused);
        std::cout << "Game paused!" << std::endl;
    }
}

// Helper function to handle toggling specific game rules
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

// Main event processing function
void processEvent(sf::Event& event, Game_Manager& gameStateManager) {
    if (event.type == sf::Event::KeyPressed) {
        if (!gameStateManager.isPaused()) {
        // Handle rules with the helper function
            handleGameRuleEvent(event.key.code, gameStateManager);

            // Handle obstacle mode toggle
            if (event.key.code == sf::Keyboard::D) {
                toggleObstacleMode(gameStateManager);
            }
        }
        // Handle pause toggle
        if (event.key.code == sf::Keyboard::P) {
            togglePause(gameStateManager);
        }
        
    }
}

void renderPauseScreen(sf::RenderWindow& window, sf::Text& pauseText, sf::Text& deleteText, const Game_Manager& gameStateManager) {
    window.clear(sf::Color::Black);
    window.draw(pauseText);

    if (!gameStateManager.isPlacing()) {
        window.draw(deleteText);
    }

    window.display();
}

sf::Text renderText(const std::string& textString, const sf::Font& font, unsigned int charSize, const sf::Color& color, const sf::Vector2f& position) {
    sf::Text text;
    text.setFont(font);
    text.setString(textString);
    text.setCharacterSize(charSize);
    text.setFillColor(color);
    text.setPosition(position);

    // Return the text object instead of drawing it directly
    return text;
}
