#include <SFML/Graphics.hpp>
#include "Player.h"
#include <cmath>

Player::Player()
{
	std::string path = "Assets/sprite.png";
#ifdef _WIN32
    path = "Assets\\sprite.png";
#endif

	if (!texture.loadFromFile(path)) {
		// error handling
	}

	sprite.setPosition(sf::Vector2f(960.f, 540.f));
	sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2.f, texture.getSize().y / 2.f));
	sprite.setRotation(rotation);
}

void Player::Movement()
{
    float speed = 5.0f;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        float xVector = std::cos(degreesToRadians(rotation.asDegrees())) * speed;
        float yVector = std::sin(degreesToRadians(rotation.asDegrees())) * speed;
        
        sf::Vector2f newPos = sprite.getPosition() + sf::Vector2f(xVector, yVector);
        
        if (!isCollidingWithWalls(newPos))
        {
            sprite.setPosition(newPos);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        float xVector = std::cos(degreesToRadians(rotation.asDegrees())) * speed;
        float yVector = std::sin(degreesToRadians(rotation.asDegrees())) * speed;
        
        sf::Vector2f newPos = sprite.getPosition() + sf::Vector2f(-xVector, -yVector);
        
        if (!isCollidingWithWalls(newPos))
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

bool Player::isCollidingWithWalls(const sf::Vector2f& newPosition)
{
    float radius = 25.0f;  // PLAYER_SIZE / 2
    
    // Check borders
    if (newPosition.x - radius < 50.f || newPosition.x + radius > 1920 - 50.f ||
        newPosition.y - radius < 50.f || newPosition.y + radius > 1080 - 50.f)
    {
        return true;
    }
    
    // Check against black rectangle (400, 300, 150)
    if (newPosition.x + radius > 400.f && newPosition.x - radius < 550.f &&
        newPosition.y + radius > 300.f && newPosition.y - radius < 450.f)
    {
        return true;
    }
    
    return false;
}

float Player::degreesToRadians(float degrees)
{
	return degrees * 3.14159265359f / 180.f;
}