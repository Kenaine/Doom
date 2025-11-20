#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "Player.h"

class Wall;

class RayCaster
{
private:
    std::vector<Wall*> wallObjects;  // Change to Wall pointers
    sf::VertexArray rayFan;
    std::vector<sf::VertexArray> intersections;

    float maxRayDistance = 1000.f;
    int rayCount = 60;
    float fov = 60.f;

public:
    RayCaster(std::vector<Wall*>& wallObjects);  // Change parameter
    void castRays(Player& player);
    void draw(sf::RenderWindow& window);
    sf::Vector2f castSingleRay(Player& player, float angle, float& distance);
    bool lineIntersection(const sf::Vector2f& rayStart, const sf::Vector2f& rayEnd,
        const sf::Vector2f& wallStart, const sf::Vector2f& wallEnd,
        sf::Vector2f& intersection);
};