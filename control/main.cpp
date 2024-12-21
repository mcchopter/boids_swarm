#include <SFML/Graphics.hpp>
#include <iostream>
#include "../objects/header/game_manager.h"  // Ensure this header is included
#include "../objects/header/functions.h"  // Include the functions header to use the inlined functions

int main() {

    
    // Initialize window
    sf::Clock clock;
    sf::RenderWindow window(sf::VideoMode(800, 600), "FPS Monitor");
    window.setFramerateLimit(60);

    // Create the Game_Manager instance
    Game_Manager gameManager;

    // Load a font (if necessary for displaying messages)
    if (!gameManager.loadFont("../data/arial.ttf")) {
        return -1;  // Exit if font cannot be loaded
    }

    // Main game loop
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        window.clear();
        sf::Event event;
        
        // Handle events (like key presses, etc.)
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Process other events, such as key presses
            processEvent(event, gameManager);  // Use the inline toggle functions inside this function
        }

        // Clear screen, draw everything, and display the window
        window.clear();
        
        // You would typically draw game objects here
        // For example: window.draw(someDrawableObject);
        
        window.display();
        window.setTitle("FPS: " + std::to_string(static_cast<int>(1.f / deltaTime.asSeconds())));
    }

    return 0;
}
