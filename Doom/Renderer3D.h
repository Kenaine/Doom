#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

class Renderer3D
{
public:
    Renderer3D(int screenWidth, int screenHeight);
    void render(sf::RenderWindow& window, const std::vector<float>& distances);

private:
    int screenWidth;
    int screenHeight;
    int fov;
};