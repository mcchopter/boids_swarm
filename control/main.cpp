#include "../objects/header/functions.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Pause Feature");
    sf::Clock clock;
    sf::Clock inputClock;  // Track time between key presses
    bool held = false;

    // Initialize Game Manager
    Game_Manager gameStateManager;
    if (!gameStateManager.loadFont("../data/arial.ttf")) {
        return -1;  // Exit if font loading fails
    }

    // Create text objects using Game_Manager's font
    sf::Text pauseText = renderText("Paused", gameStateManager.getFont(), 40, sf::Color::White, sf::Vector2f(300, 250));
    
    // Placeholder for game elements (boids or other game objects)
    std::vector<sf::CircleShape> gameElements;
    for (int i = 0; i < 5; i++) {
        sf::CircleShape boid(10.0f);  // Circle with radius 10
        boid.setPosition(100 + i * 50, 300);  // Spread horizontally
        boid.setFillColor(sf::Color::Green);
        gameElements.push_back(boid);
    }

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();  // Handle window close event
            }

            // Handle pause/unpause toggle with debounce
            if (event.type == sf::Event::KeyPressed && !held && inputClock.getElapsedTime().asSeconds() > 0.3f) {
                processEvent(event, gameStateManager);  // Handle custom user input
                held = true;
                inputClock.restart();  // Reset the input clock
            }

            if (event.type == sf::Event::KeyReleased) {
                held = false;
            }
        }

        window.clear(sf::Color::Blue);  // Clear screen with a background color

        // **Game Logic**: Handle game logic only if not paused
        sf::Time dt = clock.restart();  // Restart clock and get delta time
        if (gameStateManager.isPaused()) {
            // Do not update boids if paused
            window.draw(pauseText);  // Draw pause text when game is paused
        } else {
            // **Game Logic**: Update game objects (e.g., moving boids)
            for (auto& boid : gameElements) {
                sf::Vector2f position = boid.getPosition();
                float speed = 100.0f;  // Speed in pixels per second
                boid.setPosition(position.x + speed * dt.asSeconds(), position.y);

                // Wrap boids around the screen
                if (boid.getPosition().x > window.getSize().x) {
                    boid.setPosition(0, position.y);  // Reset position to left edge
                } else if (boid.getPosition().x < 0) {
                    boid.setPosition(window.getSize().x, position.y);  // Reset position to right edge
                }
            }
        }

        // **Game Rendering**: Draw game objects
        for (const auto& boid : gameElements) {
            window.draw(boid);  // Draw each boid (or other game objects)
        }

        window.display();  // Present the final rendered frame
    }

    return 0;
}
