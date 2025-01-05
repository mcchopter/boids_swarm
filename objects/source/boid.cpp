#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "../header/boid.h"


// Constructor
Boid::Boid(float sX, float sY, float iVelMag, float iAccMag, float sAngle)
    : x(sX), y(sY), velMag(iVelMag), accMag(iAccMag), angle(sAngle) {
    initializeShapes();
}


// Getters for position
float Boid::getX() const {
    return x;
}

float Boid::getY() const {
    return y;
}

void Boid::setTargetTurnAngle(float newAngle) {
    targetTurnAngle = newAngle;
}

void Boid::initializeShapes() {
    shape.setPointCount(3);
    shape.setPoint(0, sf::Vector2f(0, -10)); // Tip
    shape.setPoint(1, sf::Vector2f(-5, 5));  // Left base
    shape.setPoint(2, sf::Vector2f(5, 5));   // Right base
    shape.setFillColor(sf::Color::Green);
    shape.setOrigin(0, 0);

    innerCircle.setRadius(innerRadius);
    innerCircle.setFillColor(sf::Color::Transparent);
    innerCircle.setOutlineColor(sf::Color::Red);
    innerCircle.setOutlineThickness(1.0f);

    outerCircle.setRadius(outerRadius);
    outerCircle.setFillColor(sf::Color::Transparent);
    outerCircle.setOutlineColor(sf::Color::Blue);
    outerCircle.setOutlineThickness(1.0f);
}

void Boid::updatePosition(sf::RenderWindow& window) {
    shape.setPosition(x, y);
    shape.setRotation(angle);
    wrapAround(window.getSize().x, window.getSize().y);
}

void Boid::draw(sf::RenderWindow& window, bool showVision) {
    window.draw(shape);
    if (showVision) {
        drawVision(window);
    }
}

void Boid::drawVision(sf::RenderWindow& window) {
    innerCircle.setPosition(x - innerRadius, y - innerRadius);
    outerCircle.setPosition(x - outerRadius, y - outerRadius);
    window.draw(innerCircle);
    window.draw(outerCircle);
}

void Boid::update(sf::Time deltaTime, float width, float height) {
    float angleDiff = targetTurnAngle - angle;

    if (angleDiff > 180.f) angleDiff -= 360.f;
    if (angleDiff < -180.f) angleDiff += 360.f;

    if (std::abs(angleDiff) > 20.0f) {
        velMag = std::max(velMag - accMag * cohesionWeight * deltaTime.asSeconds(), minSpeed);
        maxAngle = ((maxForce * deltaTime.asSeconds()) / velMag) * 180 / M_PI;

        if (std::abs(angleDiff) <= maxAngle) {
            angle += angleDiff;
        } else {
            angle += (angleDiff > 0) ? maxAngle : -maxAngle;
        }

        shape.setRotation(angle + 90);
    } else {
        velMag = std::min(velMag + accMag * deltaTime.asSeconds(), maxSpeed);
    }

    x += velMag * std::cos(angle * M_PI / 180.f) * deltaTime.asSeconds();
    y += velMag * std::sin(angle * M_PI / 180.f) * deltaTime.asSeconds();
    wrapAround(width, height);
    shape.setPosition(x, y);
}

void Boid::setNeighbors(const std::vector<Boid>& boids, float width, float height) {
    float innerRadiusSquared = innerRadius * innerRadius;
    float outerRadiusSquared = outerRadius * outerRadius;
    bool needSeparation = false;

    avgX = x;
    avgY = y;
    int neighborCount = 0;

    for (const auto& boid : boids) {
        if (&boid != this) {
            float dx = boid.getX() - x;
            float dy = boid.getY() - y;

            if (std::abs(dx) > width / 2) dx = (dx > 0) ? dx - width : dx + width;
            if (std::abs(dy) > height / 2) dy = (dy > 0) ? dy - height : dy + height;

            float distanceSquared = dx * dx + dy * dy;

            if (distanceSquared < innerRadiusSquared) {
                applySeparation(boid, distanceSquared);
                needSeparation = true;
            } else if (distanceSquared < outerRadiusSquared) {
                avgX += boid.getX();
                avgY += boid.getY();
                neighborCount++;
            }
        }
    }

    if (neighborCount > 0 && !needSeparation) {
        avgX /= (neighborCount+1);
        avgY /= (neighborCount+1);
        applyCohesion();
    }
}

void Boid::applySeparation(const Boid& other, float distanceSquared) {
    float distance = std::sqrt(distanceSquared);
    distance = std::max(distance, 1e-5f);

    float angleToOther = std::atan2(other.getY() - y, other.getX() - x) * 180 / M_PI;
    float angleDiff = angle - angleToOther;

    angleDiff = std::fmod(angleDiff + 180.0f, 360.0f);
    if (angleDiff < 0) angleDiff += 360.0f;
    angleDiff -= 180.0f;

    targetTurnAngle += (angleDiff / distance) * separationWeight;
}

void Boid::applyCohesion() {
    float angleToCenter = std::atan2(avgY - y, avgX - x) * 180.f / M_PI;
    targetTurnAngle = angleToCenter * cohesionWeight;
}

void Boid::wrapAround(float width, float height) {
    if (x < 0) x += width;
    if (y < 0) y += height;
    if (x >= width) x -= width;
    if (y >= height) y -= height;
}
