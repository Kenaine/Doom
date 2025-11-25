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
    sf::Vector2f pos = sprite.getPosition();

    // Compute forward movement vector
    float rad = degreesToRadians(rotation.asDegrees());
    sf::Vector2f forward(std::cos(rad), std::sin(rad));

    sf::Vector2f movement(0.f, 0.f);

    // Forward / Backward
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        movement += forward * speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        movement -= forward * speed;

    // Rotation
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        rotation += sf::degrees(-rotationSpeed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        rotation += sf::degrees(rotationSpeed);

    // Attempt full movement
    sf::Vector2f newPos = pos + movement;

    bool blockedFull = isCollidingWithWalls(newPos, wallObjects);

    if (!blockedFull)
    {
        sprite.setPosition(newPos);
    }
    else
    {
        // Try X axis only
        sf::Vector2f tryX(pos.x + movement.x, pos.y);
        bool blockedX = isCollidingWithWalls(tryX, wallObjects);

        // Try Y axis only
        sf::Vector2f tryY(pos.x, pos.y + movement.y);
        bool blockedY = isCollidingWithWalls(tryY, wallObjects);

        if (!blockedX)
            sprite.setPosition(tryX);
        else if (!blockedY)
            sprite.setPosition(tryY);
        // else: both blocked → no move
    }

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