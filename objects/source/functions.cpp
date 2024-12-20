#include"../header/functions.h"

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

void processEvent(sf::Event& event, Game_Manager& gameStateManager) {
    // rest of runtime logic goes here
    /**
     * Place boid (Interaction)
     * Clear all boids
     * Place Obstacle
     * Remove Obstacle
     * Draw Boid visions and radius (Gamerules)
     * Control acceleration
     * Control Cohesion
     * Control Direction
     * Control Separation
     */

    if (event.type == sf::Event::KeyPressed) {
        // Handle rules
        if (event.key.code == sf::Keyboard::V) {
            toggleRule(gameStateManager, Game_Rule::ShowVision, "ShowVision");
        }
        if (event.key.code == sf::Keyboard::C) {
            toggleRule(gameStateManager, Game_Rule::BoidCohesion, "Boid Cohesion");
        }
        if (event.key.code == sf::Keyboard::S) {
            toggleRule(gameStateManager, Game_Rule::BoidSeparation, "Boid Separation");
        }
        if (event.key.code == sf::Keyboard::A) {
            toggleRule(gameStateManager, Game_Rule::VariableAngle, "Variable Angle");
        }
        if (event.key.code == sf::Keyboard::Z) {
            toggleRule(gameStateManager, Game_Rule::VariableVelocity, "Variable Velocity");
        }

        // Handle obstacle mode
        if (event.key.code == sf::Keyboard::D) {
            toggleObstacleMode(gameStateManager);
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

void createAndAddMessage(Game_Manager& gameStateManager, const std::string& textString, const sf::Font& font, unsigned int charSize, const sf::Color& color, const sf::Vector2f& position, float duration, const std::string& category) {
    sf::Text text;
    text.setFont(font);
    text.setString(textString);
    text.setCharacterSize(charSize);
    text.setFillColor(color);
    text.setPosition(position);

    gameStateManager.addMessage(text, duration, category);
}