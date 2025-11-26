#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "Player.h"
#include "Wall.h"

class Wall;

class RayCaster
{

    public:
        RayCaster(std::vector<Wall>& wallObjects);  // Change parameter
        void castRays(Player&);
        void checkPlayerOnView(Player&, Player&);
        void draw(sf::RenderWindow&);

        std::vector<float>& getDistances() { return distances; }
        float getMaxRayDistance() const { return maxRayDistance; }
        float getFOV() const { return fov.asDegrees(); }

    private:
        std::vector<Wall> wallObjects;  
        sf::VertexArray rayFan;
        std::vector<float> distances;

        float maxRayDistance = 5000.f;
        int vertexCount = 2400;
        sf::Angle fov = sf::degrees(60.f);

        sf::Vector2f castSingleRay(Player& player, float angle, float& distance);
        bool lineIntersection(const sf::Vector2f& rayStart, const sf::Vector2f& rayEnd,
            const sf::Vector2f& wallStart, const sf::Vector2f& wallEnd,
            sf::Vector2f& intersection);

};