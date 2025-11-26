#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Wall;

class Player
{
public:
    Player(std::vector<sf::Keyboard::Key>&, float, float);
    void Movement(const std::vector<Wall>& wallObjects);
    void Draw(sf::RenderWindow& window);
    sf::Sprite& getSprite() { return sprite; }
    
private:
    std::vector<sf::Keyboard::Key> movementKeys;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Angle rotation;
    float speed = 10.f, rotationSpeed = 2.2f, size = 20.f;
    
    float degreesToRadians(float degrees);
    bool isCollidingWithWalls(const sf::Vector2f& newPosition, const std::vector<Wall>& wallObjects);
};