#include "Renderer3D.h"
#include "RayCaster.h"
#include "Player.h"

Renderer3D::Renderer3D(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight), fov(60)
{
}

void Renderer3D::render(sf::RenderWindow& window, const std::vector<float>& distances)
{
    float sliceWidth = static_cast<float>(screenWidth) / distances.size();
    float fovRad = fov * 3.14159265359f / 180.f;
    float angleStep = fovRad / distances.size();
    float startAngle = -fovRad / 2.f;
    
    for (size_t i = 0; i < distances.size(); i++)
    {
        float distance = distances[i];
        float rayAngle = startAngle + (angleStep * i);
        
        // Correct for fish-eye by using perpendicular distance
        float correctedDistance = distance * std::cos(rayAngle);
        
        // Avoid division by zero and cap minimum distance
        if (correctedDistance < 1.f) correctedDistance = 1.f;
        
        // Calculate wall height based on distance (perspective)
        float wallHeight = (screenHeight * 200.f) / correctedDistance;
        wallHeight = std::min(static_cast<float>(screenHeight), wallHeight);
        
        // Calculate brightness based on distance (fog effect)
        float brightness = 255.f / (1.f + (correctedDistance / 1000.f));
        brightness = std::min(255.f, std::max(0.f, brightness));
        
        // Draw vertical wall slice
        sf::RectangleShape wallSlice(sf::Vector2f(sliceWidth, wallHeight));
        wallSlice.setPosition(sf::Vector2f(i * sliceWidth, (screenHeight - wallHeight) / 2.f));
        wallSlice.setFillColor(sf::Color(
            static_cast<int>(brightness),
            static_cast<int>(brightness),
            static_cast<int>(brightness)
        ));
        
        window.draw(wallSlice);
    }
}