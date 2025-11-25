#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
#include "RayCaster.h"
#include "Wall.h"
#include "Render3D.h"

const int SCREEN_WIDTH = 1920, SCREEN_HEIGHT = 1080, BORDER_SIZE = 50;
const float PLAYER_SIZE = 50.f;

using namespace std;

void InitializeWalls();
void DrawObjects(sf::RenderWindow&);

std::vector<Wall> wallObjects;  // Add this to keep Wall objects alive

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "SFML works!", sf::Style::Default, sf::State::Windowed);
    sf::View player1View(sf::FloatRect({0.f, 0.f}, {static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT)}));
    player1View.setViewport(sf::FloatRect({0.f, 0.f}, {0.5f, 0.5f}));
    window.setView(player1View);

    vector<sf::Keyboard::Key> movementKeys = {sf::Keyboard::Key::W, sf::Keyboard::Key::S, sf::Keyboard::Key::A, sf::Keyboard::Key::D};
    vector<sf::Keyboard::Key> player2Movement = {sf::Keyboard::Key::I, sf::Keyboard::Key::K, sf::Keyboard::Key::J, sf::Keyboard::Key::L};
    
    Player player(movementKeys, 1800.f, 980.f);
    Player player2(player2Movement, 200.f, 200.f);

    InitializeWalls();
    RayCaster rayCaster(wallObjects);
    RayCaster rayCaster2(wallObjects);
    Render3D renderer3D(static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT));

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        player.Movement(wallObjects);
        player2.Movement(wallObjects);
        
        rayCaster.castRays(player);
        rayCaster2.castRays(player2);   

        window.clear(sf::Color::White);
        //DrawObjects(window);
        //rayCaster.draw(window);
        //rayCaster2.draw(window);
        renderer3D.draw(window, rayCaster.getDistances(), player.getSprite().getRotation().asRadians(), rayCaster.getMaxRayDistance());
        //window.draw(player.getSprite());
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