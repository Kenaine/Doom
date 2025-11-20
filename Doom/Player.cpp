#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Wall.h"
#include <cmath>

Player::Player() : sprite(texture)
{
    std::string path = "Assets/sprite.png";
#ifdef _WIN32
    path = "Assets\\sprite.png";
#endif

    if (!texture.loadFromFile(path)) {
        // error handling
    }
    
    // Start at bottom-right entrance, moved down more
    sprite.setPosition(sf::Vector2f(1800.f, 980.f));  // Changed from 950.f to 980.f
    sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2.f, texture.getSize().y / 2.f));
    sprite.setRotation(rotation);
    
    sprite.setScale(sf::Vector2f(1.5f, 1.5f));
}

void Player::Movement(const std::vector<Wall>& wallObjects)
{
    float speed = 5.0f;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        float xVector = std::cos(degreesToRadians(rotation.asDegrees())) * speed;
        float yVector = std::sin(degreesToRadians(rotation.asDegrees())) * speed;
        
        sf::Vector2f newPos = sprite.getPosition() + sf::Vector2f(xVector, yVector);
        
        if (!isCollidingWithWalls(newPos, wallObjects))
        {
            sprite.setPosition(newPos);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        float xVector = std::cos(degreesToRadians(rotation.asDegrees())) * speed;
        float yVector = std::sin(degreesToRadians(rotation.asDegrees())) * speed;
        
        sf::Vector2f newPos = sprite.getPosition() + sf::Vector2f(-xVector, -yVector);
        
        if (!isCollidingWithWalls(newPos, wallObjects))
        {
            sprite.setPosition(newPos);
        }
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        rotation += sf::degrees(-3.0f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        rotation += sf::degrees(3.0f);
    }
    
    // Apply rotation to sprite
    sprite.setRotation(rotation);
}

bool Player::isCollidingWithWalls(const sf::Vector2f& newPosition, const std::vector<Wall>& wallObjects)
{
    float radius = 20.0f;
    
    // Check borders
    if (newPosition.x - radius < 50.f || newPosition.x + radius > 1920 - 50.f ||
        newPosition.y - radius < 50.f || newPosition.y + radius > 1080 - 50.f)
        return true;
    
    // Check collision with all walls
    for (const auto& wall : wallObjects)
    {
        if (wall.isCollidingWith(newPosition, radius))
            return true;
    }
    
    return false;
}

float Player::degreesToRadians(float degrees)
{
	return degrees * 3.14159265359f / 180.f;
}