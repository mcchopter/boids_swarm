#ifndef BOID_H
#define BOID_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

class Boid {
private:
    float maxForce = 100.0f;       // Maximum force
    float maxSpeed = 100.0f;       // Maximum velocity
    float minSpeed = 50.0f;        // Minimum velocity
    float innerRadius = 25.0f;     // Inner radius for separation
    float outerRadius = 150.0f;    // Outer radius for alignment

    float x = 0.0f, y = 0.0f;      // Position
    float velMag = 0.0f;           // Velocity magnitude
    float accMag = 0.0f;           // Acceleration magnitude
    float angle = 0.0f;            // Current angle
    float maxAngle = 45.0f;        // Maximum angle change
    float targetTurnAngle = 0.0f;  // Target turning angle
    float avgX = 0.0f, avgY = 0.0f;// Averages for cohesion calculations

    sf::ConvexShape shape;         // Shape for the boid
    sf::CircleShape innerCircle;   // Vision inner circle
    sf::CircleShape outerCircle;   // Vision outer circle

    float cohesionWeight = 1.0f;   // Weight for cohesion
    float separationWeight = 3.0f; // Weight for separation

public:
    // Constructor with optional parameters
    Boid(float sX = 0.0f, float sY = 0.0f, float iVelMag = 50.0f, 
         float iAccMag = 10.0f, float sAngle = 0.0f);

    // Getters
    float getX() const;
    float getY() const;

    // Setters
    void setTargetTurnAngle(float newAngle);

    // Initialization
    void initializeShapes();

    // Updates
    void updatePosition(sf::RenderWindow& window);
    void update(sf::Time deltaTime, float width, float height);
    void setNeighbors(const std::vector<Boid>& boids, float width, float height);

    // Drawing
    void draw(sf::RenderWindow& window, bool showVision);
    void drawVision(sf::RenderWindow& window);

    // Boid behavior
    void applySeparation(const Boid& other, float distanceSquared);
    void applyCohesion();

    // Utilities
    void wrapAround(float width, float height);
};

#endif // BOID_H
