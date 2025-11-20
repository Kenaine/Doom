#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
#include "RayCaster.h"
#include "Wall.h"

const int SCREEN_WIDTH = 1920, SCREEN_HEIGHT = 1080, BORDER_SIZE = 50;
const float PLAYER_SIZE = 50.f;

using namespace std;

void InitializeWalls();
void setWalls(sf::VertexArray*, sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f);
void DrawObjects(sf::RenderWindow&);

vector<sf::VertexArray*> Objects;
std::vector<sf::VertexArray*> walls;
std::vector<Wall> wallObjects;  // Add this to keep Wall objects alive
RayCaster* rayCaster = nullptr;

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "SFML works!", sf::Style::Default, sf::State::Windowed);
    Player player;

    InitializeWalls();
    rayCaster = new RayCaster(Objects);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        player.Movement(wallObjects);
        rayCaster->castRays(player);

        window.clear(sf::Color::White);
        DrawObjects(window);
        rayCaster->draw(window);
        window.draw(player.getSprite());
        window.display();
    }

    delete rayCaster;
    return 0;
}

void InitializeWalls()
{
    sf::VertexArray* borderWalls = new sf::VertexArray(sf::PrimitiveType::LineStrip, 5);
    setWalls(borderWalls, sf::Vector2f(0.f + BORDER_SIZE, 0.f + BORDER_SIZE), sf::Vector2f(SCREEN_WIDTH - BORDER_SIZE, 0.f + BORDER_SIZE),
        sf::Vector2f(SCREEN_WIDTH - BORDER_SIZE, SCREEN_HEIGHT - BORDER_SIZE), sf::Vector2f(0.f + BORDER_SIZE, SCREEN_HEIGHT - BORDER_SIZE));

    Objects.push_back(borderWalls);

    float thickness = 20.f;  // Wall thickness
    
    // Top row of boxes (3 boxes with vertical dividers)
    wallObjects.push_back(Wall(100.f, 120.f, 250.f, thickness));
    wallObjects.push_back(Wall(600.f, 120.f, 1200.f, thickness));
    wallObjects.push_back(Wall(100.f, 800.f, 1500.f, thickness));

    
    wallObjects.push_back(Wall(100.f, 120.f, thickness, 700.f));     
    wallObjects.push_back(Wall(1800.f, 120.f, thickness, 700.f));    
    
    
    // Add all walls to Objects for rendering
    for (auto& wall : wallObjects)
    {
        Objects.push_back(wall.getVertices());
    }
}

void setWalls(sf::VertexArray* wall, sf::Vector2f point1, sf::Vector2f point2, sf::Vector2f point3, sf::Vector2f point4)
{
    (*wall)[0].position = point1;
    (*wall)[1].position = point2;
    (*wall)[2].position = point3;
    (*wall)[3].position = point4;
    (*wall)[4].position = point1;

    (*wall)[0].color = sf::Color::Red;
    (*wall)[1].color = sf::Color::Red;
    (*wall)[2].color = sf::Color::Red;
    (*wall)[3].color = sf::Color::Red;
    (*wall)[4].color = sf::Color::Red;
}

void DrawObjects(sf::RenderWindow& window)
{
    for (auto object : Objects)
    {
        window.draw(*object);
    }
}