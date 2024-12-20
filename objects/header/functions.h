#pragma once

#include"game_manager.h"



void toggleRule(Game_Manager& gameStateManager, Game_Rule rule, const std::string& ruleName);

void toggleObstacleMode(Game_Manager& gameStateManager);

void togglePause(Game_Manager& gameStateManager);

void processEvent(sf::Event& event, Game_Manager& gameStateManager);

void renderPauseScreen(sf::RenderWindow& window, sf::Text& pauseText, sf::Text& deleteText, const Game_Manager& gameStateManager);

sf::Text renderText(const std::string& textString, const sf::Font& font, unsigned int charSize, const sf::Color& color, const sf::Vector2f& position);

void createAndAddMessage(Game_Manager& gameStateManager, const std::string& textString, const sf::Font& font, unsigned int charSize, const sf::Color& color, const sf::Vector2f& position, float duration, const std::string& category);
