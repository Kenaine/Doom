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
void DrawObjects(sf::RenderWindow&);

std::vector<Wall> wallObjects;  // Add this to keep Wall objects alive

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "SFML works!", sf::Style::Default, sf::State::Windowed);
    Player player;

    InitializeWalls();
    RayCaster rayCaster(wallObjects);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        player.Movement(wallObjects);
        rayCaster.castRays(player);

        window.clear(sf::Color::White);
        DrawObjects(window);
        rayCaster.draw(window);
        window.draw(player.getSprite());
        window.display();
    }

    return 0;
}

void InitializeWalls()
{
    float thickness = 20.f;

    //Create Boundary Walls
    wallObjects.push_back(Wall(BORDER_SIZE, BORDER_SIZE, SCREEN_WIDTH - 2 * BORDER_SIZE, thickness)); // Top Wall
    wallObjects.push_back(Wall(BORDER_SIZE, SCREEN_HEIGHT - BORDER_SIZE - thickness, SCREEN_WIDTH - 2 * BORDER_SIZE, thickness)); // Bottom Wall
    wallObjects.push_back(Wall(BORDER_SIZE, BORDER_SIZE, thickness, SCREEN_HEIGHT - 2 * BORDER_SIZE)); // Left Wall
    wallObjects.push_back(Wall(SCREEN_WIDTH - BORDER_SIZE - thickness, BORDER_SIZE, thickness, SCREEN_HEIGHT - 2 * BORDER_SIZE)); // Right Wall
    
    // Create all wall objects for collision and rendering
    wallObjects.push_back(Wall(100.f, 120.f, 250.f, thickness));
    wallObjects.push_back(Wall(600.f, 120.f, 1200.f, thickness));
    wallObjects.push_back(Wall(100.f, 800.f, 1500.f, thickness));

    // Horizontal inner walls
    wallObjects.push_back(Wall(350.f, 350.f, 450.f, thickness));
    wallObjects.push_back(Wall(350.f, 600.f, 700.f, thickness));
    wallObjects.push_back(Wall(1050.f, 350.f, 550.f, thickness));
    
    // Vertical inner walls
    wallObjects.push_back(Wall(350.f, 120.f, thickness, 250.f));
    wallObjects.push_back(Wall(1050.f, 120.f, thickness, 500.f));
    wallObjects.push_back(Wall(1580.f, 600.f, thickness, 200.f));
    wallObjects.push_back(Wall(1320.f, 350.f, thickness, 270.f));

    
    // Vertical Borders
    wallObjects.push_back(Wall(100.f, 120.f, thickness, 700.f));     
    wallObjects.push_back(Wall(1800.f, 120.f, thickness, 700.f));
    
}

void setWalls(sf::VertexArray& wall, sf::Vector2f point1, sf::Vector2f point2, sf::Vector2f point3, sf::Vector2f point4)
{
    wall[0].position = point1;
    wall[1].position = point2;
    wall[2].position = point3;
    wall[3].position = point4;
    wall[4].position = point1;

    wall[0].color = sf::Color::Red;
    wall[1].color = sf::Color::Red;
    wall[2].color = sf::Color::Red;
    wall[3].color = sf::Color::Red;
    wall[4].color = sf::Color::Red;
}

void DrawObjects(sf::RenderWindow& window)
{
    // Draw walls using vertex arrays
    for (auto wall : wallObjects)
    {
        window.draw(wall.getVertices());
    }
}