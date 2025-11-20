#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Wall
{
public:
    Wall(float x, float y, float size)
    {
        // Create a square using a LineStrip (4 corners + closing point)
        vertices.setPrimitiveType(sf::PrimitiveType::LineStrip);

        sf::Vertex v1;
        v1.position = sf::Vector2f(x, y);
        v1.color = sf::Color::Black;
        vertices.append(v1);

        sf::Vertex v2;
        v2.position = sf::Vector2f(x + size, y);
        v2.color = sf::Color::Black;
        vertices.append(v2);

        sf::Vertex v3;
        v3.position = sf::Vector2f(x + size, y + size);
        v3.color = sf::Color::Black;
        vertices.append(v3);

        sf::Vertex v4;
        v4.position = sf::Vector2f(x, y + size);
        v4.color = sf::Color::Black;
        vertices.append(v4);

        sf::Vertex v5;
        v5.position = sf::Vector2f(x, y);
        v5.color = sf::Color::Black;
        vertices.append(v5);
    }

    sf::VertexArray* getVertices() { return &vertices; }

private:
    sf::VertexArray vertices;
};