#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Wall;

class Player
{
public:
    Player();
    void Movement(std::vector<Wall>& wallObjects);
    sf::Sprite& getSprite();

private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f velocity;
    sf::Angle rotation;
    
    bool isCollidingWithWalls(const sf::Vector2f& newPosition, const std::vector<Wall>& wallObjects);
    float degreesToRadians(float degrees);
};