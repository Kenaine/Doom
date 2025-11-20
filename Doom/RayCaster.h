#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "Player.h"

class Wall;

class RayCaster
{
public:
    RayCaster(std::vector<Wall*>& wallObjects);
    void castRays(Player& player);
    void draw(sf::RenderWindow& window);
    sf::Vector2f castSingleRay(Player& player, float angle, float& distance);
    bool lineIntersection(const sf::Vector2f& rayStart, const sf::Vector2f& rayEnd,
        const sf::Vector2f& wallStart, const sf::Vector2f& wallEnd,
        sf::Vector2f& intersection);
    
    std::vector<float> getDistances() const { return distances; }

private:
    std::vector<Wall*> wallObjects;
    sf::VertexArray rayFan;
    std::vector<sf::VertexArray> intersections;
    std::vector<float> distances;

    float maxRayDistance = 1000.f;
    int rayCount = 120;  // Increase from 60 to 120 for smoother walls
    float fov = 60.f;
};