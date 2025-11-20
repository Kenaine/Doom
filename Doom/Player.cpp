#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Wall.h"

extern std::vector<Wall> collisionBorderWalls;

Player::Player() : sprite(texture)
{
    std::string path = "../Assets/sprite.png";
#ifdef _WIN32
    path = "..\\Assets\\sprite.png";
#endif

    if (!texture.loadFromFile(path)) {
        std::cerr << "Failed to load texture from: " << path << std::endl;
    }
    
    std::cout << "Texture size: " << texture.getSize().x << " x " << texture.getSize().y << std::endl;
    
    sprite = sf::Sprite(texture);
    
    sprite.setPosition(sf::Vector2f(1800.f, 980.f));
    sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2.f, texture.getSize().y / 2.f));
    sprite.setRotation(rotation);
    
    sprite.setScale(sf::Vector2f(5.0f, 5.0f));
}

sf::Sprite& Player::getSprite()
{
    return sprite;
}

void Player::Movement(std::vector<Wall>& walls)
{
    float speed = 5.0f;
    sf::Vector2f oldPos = sprite.getPosition();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        float xVector = std::cos(degreesToRadians(rotation.asDegrees())) * speed;
        float yVector = std::sin(degreesToRadians(rotation.asDegrees())) * speed;
        sf::Vector2f newPos(oldPos.x + xVector, oldPos.y + yVector);

        if (!isCollidingWithWalls(newPos, walls))
        {
            sprite.setPosition(newPos);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        float xVector = std::cos(degreesToRadians(rotation.asDegrees())) * speed;
        float yVector = std::sin(degreesToRadians(rotation.asDegrees())) * speed;
        sf::Vector2f newPos(oldPos.x - xVector, oldPos.y - yVector);

        if (!isCollidingWithWalls(newPos, walls))
        {
            sprite.setPosition(newPos);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        rotation = rotation - sf::degrees(5.f);
        sprite.setRotation(rotation);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        rotation = rotation + sf::degrees(5.f);
        sprite.setRotation(rotation);
    }
    
    // Check collision with border walls
    for (auto& wall : collisionBorderWalls)
    {
        if (wall.isCollidingWith(sprite.getPosition(), 20.f))
        {
            sprite.setPosition(oldPos);
            return;
        }
    }
}

bool Player::isCollidingWithWalls(const sf::Vector2f& newPosition, const std::vector<Wall>& wallObjects)
{
    for (const auto& wall : wallObjects)
    {
        if (wall.isCollidingWith(newPosition, 20.f))
        {
            return true;
        }
    }
    return false;
}

float Player::degreesToRadians(float degrees)
{
    return degrees * 3.14159265359f / 180.f;
}