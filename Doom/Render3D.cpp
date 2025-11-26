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

void Render3D::drawPlayer(
    sf::RenderWindow& window,
    sf::Vector2f playerPos,          // camera/player position
    sf::Vector2f otherPlayerPos,     // other player's world position
    float cameraRotationRad,          // camera/player rotation in radians
    float fovDegrees,                 // FOV in degrees
    float playerWorldSize,            // size of the player in world units
    float maxRenderDistance,          // max visible distance
    size_t numRays,                   // number of rays cast
    float otherPlayerRotationRad      // other player's rotation in radians
)
{
    // Convert FOV from degrees to radians
    float fovRad = fovDegrees * 3.14159265359f / 180.f;
    
    // Vector from camera to other player
    sf::Vector2f toOther = otherPlayerPos - playerPos;
    float distance = std::sqrt(toOther.x*toOther.x + toOther.y*toOther.y);

    if (distance > maxRenderDistance) return; // too far

    // Angle from camera to player
    float angleToOther = std::atan2(toOther.y, toOther.x);
    float relativeAngle = angleToOther - cameraRotationRad;

    // Normalize to [-PI, PI]
    while (relativeAngle < -3.14159265f) relativeAngle += 2.f * 3.14159265f;
    while (relativeAngle >  3.14159265f) relativeAngle -= 2.f * 3.14159265f;

    // Ignore if outside FOV
    if (std::abs(relativeAngle) > fovRad / 2.f) return;

    // Transform to camera-relative coordinates
    // Rotate toOther by -cameraRotation to get camera space coordinates
    float cosRot = std::cos(-cameraRotationRad);
    float sinRot = std::sin(-cameraRotationRad);
    float cameraX = toOther.x * cosRot - toOther.y * sinRot;  // forward/backward
    float cameraY = toOther.x * sinRot + toOther.y * cosRot;  // left/right

    // Avoid division by zero
    if (cameraX < 0.1f) return;

    // Calculate which ray index corresponds to this player
    // This matches how draw() maps ray indices to screen pixels
    float angleStep = fovRad / numRays;
    float rayIndexFloat = (relativeAngle + fovRad * 0.5f) / angleStep;
    
    // Convert ray index to screen X coordinate
    float sliceWidth = screenWidth / numRays;
    float screenX = rayIndexFloat * sliceWidth;
    
    // screenY based on up-down offset (if player has height variance)
    // For now, keep centered vertically
    float screenY = screenHeight * 0.5f;

    // Size based on distance
    float screenSize = (playerWorldSize / cameraX) * screenHeight;
    screenSize = std::clamp(screenSize, 1.f, screenHeight);

    // Clamp screen position to be within bounds
    screenX = std::clamp(screenX, -screenSize, screenWidth + screenSize);
    screenY = std::clamp(screenY, -screenSize, screenHeight + screenSize);

    // Draw circle
    sf::CircleShape circle(screenSize);
    circle.setOrigin(sf::Vector2f(screenSize, screenSize) * 0.5f); // center origin
    circle.setPosition(sf::Vector2f(screenX, screenY));
    circle.setFillColor(sf::Color::Green);

    window.draw(circle);
    
    // Draw a line showing where the other player is looking in 3D perspective
    // The line should be rendered in the same 3D space as the circle
    
    // Calculate the other player's rotation relative to camera
    float otherPlayerRelativeRotation = otherPlayerRotationRad - cameraRotationRad;
    
    // Normalize to [-PI, PI]
    while (otherPlayerRelativeRotation < -3.14159265f) otherPlayerRelativeRotation += 2.f * 3.14159265f;
    while (otherPlayerRelativeRotation >  3.14159265f) otherPlayerRelativeRotation -= 2.f * 3.14159265f;
    
    // Create a point in front of the player in their local space
    float lookAheadDistance = playerWorldSize * 2.f; // distance they're looking
    sf::Vector2f lookDirection(std::cos(otherPlayerRotationRad), std::sin(otherPlayerRotationRad));
    sf::Vector2f lookPoint = otherPlayerPos + lookDirection * lookAheadDistance;
    
    // Now project this look point to screen space
    sf::Vector2f toLookPoint = lookPoint - playerPos;
    float angleTolookPoint = std::atan2(toLookPoint.y, toLookPoint.x);
    float relativeAngleLookPoint = angleTolookPoint - cameraRotationRad;
    
    // Normalize to [-PI, PI]
    while (relativeAngleLookPoint < -3.14159265f) relativeAngleLookPoint += 2.f * 3.14159265f;
    while (relativeAngleLookPoint >  3.14159265f) relativeAngleLookPoint -= 2.f * 3.14159265f;
    
    // Check if look point is within FOV
    if (std::abs(relativeAngleLookPoint) <= fovRad / 2.f)
    {
        // Transform look point to camera space
        float cosRotLook = std::cos(-cameraRotationRad);
        float sinRotLook = std::sin(-cameraRotationRad);
        float cameraXLook = toLookPoint.x * cosRotLook - toLookPoint.y * sinRotLook;
        
        if (cameraXLook > 0.1f)
        {
            // Calculate screen position of look point
            float rayIndexFloatLook = (relativeAngleLookPoint + fovRad * 0.5f) / angleStep;
            float screenXLook = rayIndexFloatLook * sliceWidth;
            float screenYLook = screenHeight * 0.5f;
            
            // Draw line from circle to look point
            sf::VertexArray directionLine(sf::PrimitiveType::LineStrip, 2);
            directionLine[0].position = sf::Vector2f(screenX, screenY);
            directionLine[0].color = sf::Color::Yellow;
            directionLine[1].position = sf::Vector2f(screenXLook, screenYLook);
            directionLine[1].color = sf::Color::Yellow;
            
            window.draw(directionLine);
        }
    }
}

