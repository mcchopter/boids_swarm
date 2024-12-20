#include "../objects/header/functions.h"



int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Pause Feature");
    sf::Clock clock;

    Game_Manager gameStateManager;  // Manage game states
    sf::Font font;
    
    // Load font
    if (!font.loadFromFile("../data/arial.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return -1;
    }

    // Create the text objects
    sf::Text pauseText = renderText("Paused", font, 40, sf::Color::White, sf::Vector2f(300, 250));
    sf::Text deleteText = renderText("Delete", font, 20, sf::Color::Red, sf::Vector2f(20, 10));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Pause/Unpause logic
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
                togglePause(gameStateManager);
            }

            // Check if the game is not paused
            if (!gameStateManager.isPaused()) {
                processEvent(event, gameStateManager);  // Handle user input
            }
        }

        // Check if the game is paused
        if (gameStateManager.isPaused()) {
            window.clear(sf::Color::Black);
            window.draw(pauseText);  // Draw pause text

            if (!gameStateManager.isPlacing()) {
                window.draw(deleteText);  // Draw "Delete" text when not placing
            }

            window.display();
            continue;  // Skip the rest of the game rendering since it's paused
        }

        // Game logic and rendering for the "Playing" state
        sf::Time dt = clock.restart();
        window.clear(sf::Color::Blue);  // Clear screen with blue

        // Draw game elements here...

        if (!gameStateManager.isPlacing()) {
            window.draw(deleteText);  // Draw "Delete" text when not placing
        }

        window.display();  // Update the display with new frame
    }

    return 0;
}
