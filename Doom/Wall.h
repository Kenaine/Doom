#pragma once
#include <SFML/Graphics.hpp>

class Wall
{
public:
    Wall(float x, float y, float width, float height)
        : x(x), y(y), width(width), height(height)
    {
        vertices.setPrimitiveType(sf::PrimitiveType::TriangleStrip);
        
        sf::Vertex v1;
        v1.position = sf::Vector2f(x, y);
        v1.color = sf::Color(128, 128, 128);  // Grey fill
        vertices.append(v1);
        
        sf::Vertex v2;
        v2.position = sf::Vector2f(x + width, y);
        v2.color = sf::Color(128, 128, 128);  // Grey fill
        vertices.append(v2);
        
        sf::Vertex v3;
        v3.position = sf::Vector2f(x, y + height);
        v3.color = sf::Color(128, 128, 128);  // Grey fill
        vertices.append(v3);
        
        sf::Vertex v4;
        v4.position = sf::Vector2f(x + width, y + height);
        v4.color = sf::Color(128, 128, 128);  // Grey fill
        vertices.append(v4);
    }

    sf::VertexArray* getVertices() { return &vertices; }
    
    bool isCollidingWith(const sf::Vector2f& position, float radius) const
    {
        return position.x + radius > x && position.x - radius < x + width &&
               position.y + radius > y && position.y - radius < y + height;
    }

private:
    sf::VertexArray vertices;
    float x, y, width, height;
};