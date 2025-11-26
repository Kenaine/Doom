#include "RayCaster.h"
#include "Player.h"
#include <algorithm>
#include <iostream>

RayCaster::RayCaster(std::vector<Wall>& wallObjects)
    : wallObjects(wallObjects)
{
    rayFan = sf::VertexArray(sf::PrimitiveType::TriangleFan, vertexCount + 2);
    distances.reserve(vertexCount + 1);
}

void RayCaster::checkPlayerOnView(Player& player, Player& otherPlayer)
{
    sf::Vector2f playerPos = player.getSprite().getPosition();
    sf::Vector2f otherPos = otherPlayer.getSprite().getPosition();
    sf::Vector2f toOther = otherPos - playerPos;
    float distanceToOther = std::sqrt(toOther.x * toOther.x + toOther.y * toOther.y);

    float playerRot = player.getSprite().getRotation().asRadians();
    float fovRad = fov.asRadians();

    // Compute angle to other player relative to player rotation
    float angleToOther = std::atan2(toOther.y, toOther.x);
    float relativeAngle = angleToOther - playerRot;

    // Normalize angle to [-PI, PI]
    while (relativeAngle < -3.14159265f) relativeAngle += 2.f * 3.14159265f;
    while (relativeAngle >  3.14159265f) relativeAngle -= 2.f * 3.14159265f;

    // Quick FOV & distance check
    if (std::abs(relativeAngle) > fovRad / 2.f || distanceToOther > maxRayDistance)
    {
        playerInView = false;
        return;
    }

    // --- Determine which ray in the fan corresponds to the other player ---
    size_t numRays = distances.size();
    float startAngle = -fovRad / 2.f;
    float angleStep = fovRad / static_cast<float>(numRays);

    size_t rayIndex = static_cast<size_t>((relativeAngle - startAngle) / angleStep);
    rayIndex = std::clamp(rayIndex, size_t(0), numRays - 1);

    // Compare distance along that ray to the distance to the other player
    float rayDistance = distances[rayIndex];

    if (distanceToOther <= rayDistance)
    {
        // No wall in between, player is visible
        playerInView = true;
        lastKnownPlayerPos = otherPos;
        lastKnownPlayerdistance = distanceToOther;
    }
    else
    {
        // Wall blocks view
        playerInView = false;
    }
}


void RayCaster::castRays(Player& player)
{
    distances.clear();

    sf::Vector2f playerPos = player.getSprite().getPosition();
    float playerRot = player.getSprite().getRotation().asRadians();

    rayFan[0].position = playerPos;             // center of the fan
    rayFan[vertexCount + 1].position = playerPos;

    float fovRad = fov.asRadians();
    float startAngle = playerRot - (fovRad * 0.5f);
    float angleStep = fovRad / vertexCount;

    for (int i = 0; i <= vertexCount; i++)
    {
        float angle = startAngle + angleStep * i;
        float distance = 0.f;

        sf::Vector2f hit = castSingleRay(player, angle, distance);

        rayFan[i + 1].position = hit;
        rayFan[i + 1].color = sf::Color(0, 0, 255, 120);

        distances.push_back(distance);
    }
}

sf::Vector2f RayCaster::castSingleRay(Player& player, float angle, float& distance)
{
    sf::Vector2f start = player.getSprite().getPosition();
    sf::Vector2f dir(std::cos(angle), std::sin(angle));
    sf::Vector2f end = start + dir * maxRayDistance;

    float closestDistSq = maxRayDistance * maxRayDistance;
    sf::Vector2f closestPoint = end;

    for (const Wall& wall : wallObjects)
    {
        const sf::VertexArray& verts = wall.getVertices();

        for (size_t i = 0; i < verts.getVertexCount() - 1; i++)
        {
            sf::Vector2f A = verts[i].position;
            sf::Vector2f B = verts[i + 1].position;

            sf::Vector2f hit;
            if (lineIntersection(start, end, A, B, hit))
            {
                sf::Vector2f d = hit - start;
                float distSq = d.x * d.x + d.y * d.y;

                if (distSq < closestDistSq)
                {
                    closestDistSq = distSq;
                    closestPoint = hit;
                }
            }
        }
    }

    distance = std::sqrt(closestDistSq);
    return closestPoint;
}

bool RayCaster::lineIntersection(const sf::Vector2f& rayStart, const sf::Vector2f& rayEnd,
                                 const sf::Vector2f& wallStart, const sf::Vector2f& wallEnd,
                                 sf::Vector2f& intersection)
{
    float x1 = rayStart.x, y1 = rayStart.y;
    float x2 = rayEnd.x,   y2 = rayEnd.y;
    float x3 = wallStart.x, y3 = wallStart.y;
    float x4 = wallEnd.x,   y4 = wallEnd.y;

    float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    if (den == 0) return false; // parallel

    float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
    float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;

    // t must be within ray (>= 0), and u must be on the wall (0-1)
    if (t >= 0 && u >= 0 && u <= 1)
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
}
