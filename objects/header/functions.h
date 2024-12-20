#pragma once

#include "game_manager.h"

// Toggle a specific game rule (enable/disable)
void toggleRule(Game_Manager& gameStateManager, Game_Rule rule, const std::string& ruleName);

// Toggle the obstacle mode (Place/Remove)
void toggleObstacleMode(Game_Manager& gameStateManager);

// Toggle the pause state (pause/unpause)
void togglePause(Game_Manager& gameStateManager);

// Process a specific event (keyboard, mouse, etc.)
void processEvent(sf::Event& event, Game_Manager& gameStateManager);

// Render the pause screen with relevant texts
void renderPauseScreen(sf::RenderWindow& window, sf::Text& pauseText, sf::Text& deleteText, const Game_Manager& gameStateManager);

// Helper function to render text with specific attributes
sf::Text renderText(const std::string& textString, const sf::Font& font, unsigned int charSize, const sf::Color& color, const sf::Vector2f& position);
