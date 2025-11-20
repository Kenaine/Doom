#include "RayCaster.h"
#include "Wall.h"
#include <iostream>
#include <limits>

RayCaster::RayCaster(std::vector<Wall*>& wallObjects) : wallObjects(wallObjects)
{
    intersections.reserve(rayCount);
    rayFan = sf::VertexArray(sf::PrimitiveType::TriangleFan, rayCount + 2);
}

void RayCaster::castRays(Player& player)
{
    intersections.clear();
    distances.clear();  // Clear previous distances

    sf::Vector2f playerPos = player.getSprite().getPosition();
    float playerAngle = player.getSprite().getRotation().asRadians();
    float fovRad = fov * 3.14159265359f / 180.f;
    float startAngle = playerAngle - (fovRad / 2.f);
    float angleStep = fovRad / static_cast<float>(rayCount);

    rayFan[0].position = playerPos;
    rayFan[0].color = sf::Color::Blue;

    for (int i = 0; i <= rayCount; i++)
    {
        float currentAngle = startAngle + (angleStep * i);
        float distance = 0.f;
        sf::Vector2f hitPoint = castSingleRay(player, currentAngle, distance);

        distances.push_back(distance);  // Store distance

        rayFan[i + 1].position = hitPoint;
        rayFan[i + 1].color = sf::Color(0, 0, 255, 100);

        sf::VertexArray intersectionPoint(sf::PrimitiveType::Points, 1);
        intersectionPoint[0].position = hitPoint;
        intersectionPoint[0].color = sf::Color::Red;
        intersections.push_back(intersectionPoint);
    }
}

sf::Vector2f RayCaster::castSingleRay(Player& player, float angle, float& distance)
{
    sf::Vector2f playerPos = player.getSprite().getPosition();
    sf::Vector2f rayDir(std::cos(angle), std::sin(angle));
    sf::Vector2f rayEnd = playerPos + rayDir * maxRayDistance;

    sf::Vector2f closestIntersection = rayEnd;
    float closestDistance = maxRayDistance;

    for (auto wall : wallObjects)
    {
        sf::VertexArray* vertices = wall->getVertices();
        for (size_t i = 0; i < vertices->getVertexCount() - 1; i++)
        {
            sf::Vector2f wallStart = (*vertices)[i].position;
            sf::Vector2f wallEnd = (*vertices)[i + 1].position;

            sf::Vector2f intersection;
            if (lineIntersection(playerPos, rayEnd, wallStart, wallEnd, intersection))
            {
                float dist = std::sqrt(
                    std::pow(intersection.x - playerPos.x, 2) +
                    std::pow(intersection.y - playerPos.y, 2)
                );

                if (dist < closestDistance)
                {
                    closestDistance = dist;
                    closestIntersection = intersection;
                }
            }
        }
    }

    distance = closestDistance;
    return closestIntersection;
}

bool RayCaster::lineIntersection(const sf::Vector2f& rayStart, const sf::Vector2f& rayEnd,
    const sf::Vector2f& wallStart, const sf::Vector2f& wallEnd,
    sf::Vector2f& intersection)
{
    float x1 = rayStart.x, y1 = rayStart.y;
    float x2 = rayEnd.x, y2 = rayEnd.y;
    float x3 = wallStart.x, y3 = wallStart.y;
    float x4 = wallEnd.x, y4 = wallEnd.y;

    float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    if (den == 0) return false;

    float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
    float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;

    if (t >= 0 && t <= 1 && u >= 0 && u <= 1)
    {
        intersection.x = x1 + t * (x2 - x1);
        intersection.y = y1 + t * (y2 - y1);
        return true;
    }
    return false;
}

void RayCaster::draw(sf::RenderWindow& window)
{
    window.draw(rayFan);
    for (auto& intersection : intersections)
    {
        window.draw(intersection);
    }
}