#include "../header/renderer.h"

Renderer::Renderer() {}

sf::Text Renderer::renderText(const std::string& textString, const sf::Font& font, unsigned int charSize, const sf::Color& color, const sf::Vector2f& position) {
    sf::Text text;
    text.setFont(font);
    text.setString(textString);
    text.setCharacterSize(charSize);
    text.setFillColor(color);
    text.setPosition(position);
    return text;
}
