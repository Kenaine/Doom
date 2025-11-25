#include <SFML/Graphics.hpp>
#include "Render3D.h"

Render3D::Render3D(float width, float height) : screenWidth(width), screenHeight(height)
{

}

void Render3D::draw(sf::RenderWindow& window, std::vector<float> distances, float fov)
{
    float sliceWidth = static_cast<float>(screenWidth) / distances.size();
    float fovRad = fov * 3.14159265359f / 180.f;
    float angleStep = fovRad / distances.size();
    float startAngle = -fovRad / 2.f;

    for (size_t i = 0; i < distances.size(); i++)
    {
        float distance = distances[i];

        if (distance >= 500)
            continue;
       
        float rayAngle = startAngle + (angleStep * i);

        // Correct for fish-eye effect
        float correctedDistance = distance * std::cos(rayAngle);

        // Avoid division by zero and cap minimum distance
        if (correctedDistance < 1.f) correctedDistance = 1.f;

        // Calculate wall height (perspective)
        float wallHeight = (screenHeight * 200.f) / correctedDistance;

        // ---- Distance-based shading ----
        // Brightness (fog)
        float brightness = 255.f / (1.f + (correctedDistance / 800.f));
        brightness = std::clamp(brightness, 0.f, 255.f);

        // Alpha (fade-out)
        float maxFadeDistance = 500.f;   // Adjust this for desired fade range
        float alpha = 255.f * (1.f - (correctedDistance / maxFadeDistance));
        alpha = std::clamp(alpha, 0.f, 255.f);

        // Wall slice
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
