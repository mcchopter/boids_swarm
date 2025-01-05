#include "../objects/header/functions.h"  // Include the functions header to use the inlined functions
#include "../objects/header/renderer.h"  // Include the renderer header
#include "../objects/header/boid.h" // Include the boid header
#include <cmath> // For pow function
#include <random>

int main() {

    
    // Initialize window
    sf::Clock clock;
    sf::RenderWindow window(sf::VideoMode(1400, 1400), "FPS Monitor");
    window.setFramerateLimit(60);

    // Create the Game_Manager instance
    Game_Manager gameManager;

    // Load a font (if necessary for displaying messages)
    if (!gameManager.loadFont("../data/arial.ttf")) {
        return -1;  // Exit if font cannot be loaded
    }
    
    // set up the random number distribution for initial placement
    std::random_device rd;
    std::mt19937 gen(rd());  // Mersenne Twister engine
    std::uniform_int_distribution<> dis(1, 1400);

    for (int i = 0; i < 25 ; i++) {
        gameManager.addBoid(dis(gen), dis(gen), 100, 25, 320);
    }
    // Create the Renderer instance
    Renderer renderer;
    std::cout << "Starting game loop" << std::endl;
    // Main game loop
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        
        // Handle window events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            processEvent(event, gameManager, window);
        }

        // Update the message states (i.e., decrement lifetime and remove expired)
        gameManager.updateMessages(deltaTime.asSeconds());
        if (!gameManager.isPaused()) { 
            gameManager.updateBoids(deltaTime, window.getSize().x, window.getSize().y);
        }
        // Clear and redraw everything
        window.clear();
        
        // Draw messages
        for (const auto& message : gameManager.getMessages()) {
            // If the message is related to input, start with a higher opacity.
            float initialOpacity = (message.category == Message_Category::Input) ? 200.0f : 255.0f;
            float alpha = std::max(0.0f, std::min(initialOpacity, (message.lifetime / message.initialLifetime) * 255.0f));
            sf::Color textColor = sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha));  // White color with adjusted alpha

            // Render the text with the adjusted opacity
            sf::Text text = renderer.renderText(
                message.text,
                gameManager.getFont(),
                24,
                textColor,  // Pass the adjusted color with the new alpha value
                message.position
            );

            window.draw(text);
        }

        for (auto& boid : gameManager.getBoids()) {
            boid.draw(window, gameManager.isRuleEnabled(Game_Rule::ShowVision));
        }


        window.display();
        window.setTitle("FPS: " + std::to_string(static_cast<int>(1.f / deltaTime.asSeconds())));
    }


    return 0;
}
