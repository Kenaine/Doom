#pragma once
#include <SFML/Graphics.hpp>

class Wall
{
public:
    Wall(float x, float y, float width, float height)
        : x(x), y(y), width(width), height(height)
    {
        vertices = sf::VertexArray(sf::PrimitiveType::LineStrip, 5);
        
        vertices[0].position = sf::Vector2f(x, y);
        vertices[0].color = sf::Color(128, 128, 128);  // Grey fill

        vertices[1].position = sf::Vector2f(x + width, y);
        vertices[1].color = sf::Color(128, 128, 128);  // Grey fill
        
        vertices[2].position = sf::Vector2f(x + width, y + height);
        vertices[2].color = sf::Color(128, 128, 128);  // Grey fill

        vertices[3].position = sf::Vector2f(x, y + height);
        vertices[3].color = sf::Color(128, 128, 128);  // Grey fill

        vertices[4].position = sf::Vector2f(x, y);
        vertices[4].color = sf::Color(128, 128, 128);  // Grey fill
    }

    sf::VertexArray& getVertices() { return vertices; }
    const sf::VertexArray& getVertices() const { return vertices; }
    
    bool isCollidingWith(const sf::Vector2f& position, float radius) const
    {
        return position.x + radius > x && position.x - radius < x + width &&
               position.y + radius > y && position.y - radius < y + height;
    }

private:
    sf::VertexArray vertices;
    float x, y, width, height;
};