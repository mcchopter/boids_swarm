#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include "game_manager.h"  // Include Game_Manager to access game data
#include <vector>  // Include for vector of sf::Text

class Renderer {
public:
    Renderer();

private:

    // Helper function to render text with specific attributes
    sf::Text renderText(const std::string& textString, const sf::Font& font, unsigned int charSize, const sf::Color& color, const sf::Vector2f& position);
};

#endif // RENDERER_H