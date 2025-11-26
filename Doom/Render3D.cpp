#include <SFML/Graphics.hpp>
#include "Render3D.h"
#include <algorithm>
#include <cmath>

Render3D::Render3D(float width, float height) : screenWidth(width), screenHeight(height)
{
}

void Render3D::draw(sf::RenderWindow& window, std::vector<float> distances, float fovDegrees, float maxDistance)
{
    size_t numRays = distances.size();
    if (numRays == 0) return;

    float sliceWidth = static_cast<float>(screenWidth) / numRays;
    float fovRad = fovDegrees * 3.14159265359f / 180.f;
    float angleStep = fovRad / numRays;
    float startAngle = -fovRad / 2.f; // rays relative to player viewing direction

    for (size_t i = 0; i < numRays; i++)
    {
        float rawDistance = distances[i];

        // If distance is larger than maxDistance, fade it out smoothly
        float alpha = 255.f;
        if (rawDistance > maxDistance)
        {
            alpha = 0.f; // completely invisible
            rawDistance = maxDistance; // cap for wall height calculation
        }
        else
        {
            // Fade based on distance (optional)
            alpha = 255.f * (1.f - (rawDistance / maxDistance));
        }

        float rayAngle = startAngle + i * angleStep;

        // Correct fish-eye effect by dividing by cos(rayAngle)
        float correctedDistance = rawDistance * std::cos(rayAngle);
        if (correctedDistance < 1.f) correctedDistance = 1.f; // prevent division by zero

        // Calculate wall height based on perspective
        float wallHeight = ((screenHeight * 200.f) / correctedDistance) ;

        // Optional: brightness/fog based on distance
        float brightness = 255.f / (1.f + (correctedDistance / 800.f));
        brightness = std::clamp(brightness, 0.f, 255.f);

        // Draw ceiling slice
        /*sf::RectangleShape ceilingSlice(sf::Vector2f(sliceWidth, (screenHeight - wallHeight) / 2.f));
        ceilingSlice.setPosition(sf::Vector2f(i * sliceWidth, 0.f));
        ceilingSlice.setFillColor(sf::Color(25, 100, 100, static_cast<int>(alpha))); // gray ceiling
        window.draw(ceilingSlice);*/

        // Draw floor slice

        // Draw wall slice
        sf::RectangleShape wallSlice(sf::Vector2f(sliceWidth, wallHeight));
        wallSlice.setPosition(sf::Vector2f(i * sliceWidth, (screenHeight - wallHeight) / 2.f));
        wallSlice.setFillColor(sf::Color(
            static_cast<int>(brightness),
            static_cast<int>(brightness),
            static_cast<int>(brightness),
            static_cast<int>(alpha)
        ));

        window.draw(wallSlice);
    }
}
