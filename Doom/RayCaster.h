#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "Player.h"

class Wall;

class RayCaster
{

    public:
        RayCaster(std::vector<Wall>& wallObjects);  // Change parameter
        void castRays(Player& player);
        void draw(sf::RenderWindow& window);

    private:
        std::vector<Wall> objects;  
        sf::VertexArray fan;
        std::vector<float> distances;

        float maxDistance = 1000.f;
        int vertexCount = 60;
        sf::Angle fov = sf::degrees(60.f);

        sf::Vector2f findIntersectionPoint(sf::Vector2f, sf::Vector2f, float&);
        void twoPointToLine(sf::Vector2f, sf::Vector2f, float&, float&, float&);
        bool checkIntersection(float[3], float[3], sf::Vector2f&);
        bool checkPointOnSegment(const sf::Vector2f&, const sf::Vector2f&, const sf::Vector2f&);


};