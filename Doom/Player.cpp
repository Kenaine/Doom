#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Wall.h"
#include <cmath>
#include <filesystem>

Player::Player() : sprite(texture)
{
    std::cout << std::filesystem::current_path() << std::endl;
    std::string path = "../Assets/sprite.png";
#ifdef _WIN32
    path = "..\\..\\Assets\\sprite.png";
#endif

    if (!texture.loadFromFile(path)) {
        std::cerr << "Failed to load texture from: " << path << std::endl;
    }
    
    std::cout << "Texture size: " << texture.getSize().x << " x " << texture.getSize().y << std::endl;

    // Create sprite with loaded texture
    sprite = sf::Sprite(texture);
    
    // Start at bottom-right entrance
    sprite.setPosition(sf::Vector2f(1800.f, 980.f));
    sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2.f, texture.getSize().y / 2.f));
    sprite.setRotation(rotation);
    
}

void Player::Movement(const std::vector<Wall>& wallObjects)
{
    
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
        rotation += sf::degrees(-rotationSpeed);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        rotation += sf::degrees(rotationSpeed);
    }
    
    // Apply rotation to sprite
    sprite.setRotation(rotation);
}

bool Player::isCollidingWithWalls(const sf::Vector2f& newPosition, const std::vector<Wall>& wallObjects)
{
    
    // Check borders
    if (newPosition.x - size < 50.f || newPosition.x + size > 1920 - 50.f ||
        newPosition.y - size < 50.f || newPosition.y + size > 1080 - 50.f)
        return true;
    
    // Check collision with all walls
    for (const auto& wall : wallObjects)
    {
        if (wall.isCollidingWith(newPosition, size))
            return true;
    }
    
    return false;
}

float Player::degreesToRadians(float degrees)
{
	return degrees * 3.14159265359f / 180.f;
}