#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Wall;

class Player
{
public:
    Player();
    void Movement(const std::vector<Wall>& wallObjects);
    void Draw(sf::RenderWindow& window);
    sf::Sprite& getSprite() { return sprite; }
    
private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Angle rotation;
    float speed;
    
    float degreesToRadians(float degrees);
    bool isCollidingWithWalls(const sf::Vector2f& newPosition, const std::vector<Wall>& wallObjects);
};