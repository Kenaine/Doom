#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Wall.h"
#include "RayCaster.h"
#include "Renderer3D.h"

using namespace std;

std::vector<Wall> wallObjects;
std::vector<Wall> collisionBorderWalls;
RayCaster* rayCaster;
std::vector<sf::VertexArray*> Objects;

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int BORDER_SIZE = 50;

void setWalls(sf::VertexArray* walls, sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, sf::Vector2f p4)
{
    sf::Vertex v1;
    v1.position = p1;
    v1.color = sf::Color::Red;
    walls->append(v1);
    
    sf::Vertex v2;
    v2.position = p2;
    v2.color = sf::Color::Red;
    walls->append(v2);
    
    sf::Vertex v3;
    v3.position = p3;
    v3.color = sf::Color::Red;
    walls->append(v3);
    
    sf::Vertex v4;
    v4.position = p4;
    v4.color = sf::Color::Red;
    walls->append(v4);
    
    sf::Vertex v5;
    v5.position = p1;
    v5.color = sf::Color::Red;
    walls->append(v5);
}

void InitializeWalls()
{
    sf::VertexArray* borderVA = new sf::VertexArray(sf::PrimitiveType::LineStrip, 5);
    setWalls(borderVA, sf::Vector2f(0.f + BORDER_SIZE, 0.f + BORDER_SIZE), sf::Vector2f(SCREEN_WIDTH - BORDER_SIZE, 0.f + BORDER_SIZE),
        sf::Vector2f(SCREEN_WIDTH - BORDER_SIZE, SCREEN_HEIGHT - BORDER_SIZE), sf::Vector2f(0.f + BORDER_SIZE, SCREEN_HEIGHT - BORDER_SIZE));

    Objects.push_back(borderVA);

    float thickness = 20.f;
    
    // Border walls - collision only
    collisionBorderWalls.push_back(Wall(0.f, 0.f, SCREEN_WIDTH, thickness));
    collisionBorderWalls.push_back(Wall(0.f, SCREEN_HEIGHT - thickness, SCREEN_WIDTH, thickness));
    collisionBorderWalls.push_back(Wall(0.f, 0.f, thickness, SCREEN_HEIGHT));
    collisionBorderWalls.push_back(Wall(SCREEN_WIDTH - thickness, 0.f, thickness, SCREEN_HEIGHT));
    
    // Interior walls
    wallObjects.push_back(Wall(100.f, 120.f, 250.f, thickness));
    wallObjects.push_back(Wall(600.f, 120.f, 1200.f, thickness));
    wallObjects.push_back(Wall(100.f, 800.f, 1500.f, thickness));
    wallObjects.push_back(Wall(350.f, 350.f, 450.f, thickness));
    wallObjects.push_back(Wall(350.f, 600.f, 700.f, thickness));
    wallObjects.push_back(Wall(1050.f, 350.f, 550.f, thickness));
    wallObjects.push_back(Wall(350.f, 120.f, thickness, 250.f));
    wallObjects.push_back(Wall(1050.f, 120.f, thickness, 500.f));
    wallObjects.push_back(Wall(1580.f, 600.f, thickness, 200.f));
    wallObjects.push_back(Wall(1320.f, 350.f, thickness, 270.f));
    wallObjects.push_back(Wall(100.f, 120.f, thickness, 700.f));
    wallObjects.push_back(Wall(1800.f, 120.f, thickness, 700.f));
    
    std::vector<Wall*> wallPtrs;
    for (auto& wall : wallObjects)
    {
        wallPtrs.push_back(&wall);
    }
    
    rayCaster = new RayCaster(wallPtrs);
}

void DrawObjects(sf::RenderWindow& window)
{
    for (auto& wall : wallObjects)
    {
        window.draw(*wall.getVertices());
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(SCREEN_WIDTH, SCREEN_HEIGHT)), "Doom 3D");
    Player player;

    InitializeWalls();
    Renderer3D renderer3D(window.getSize().x, window.getSize().y);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        player.Movement(wallObjects);
        rayCaster->castRays(player);

        window.clear(sf::Color::Black);
        renderer3D.render(window, rayCaster->getDistances());
        window.display();
    }

    delete rayCaster;
    return 0;
}