#pragma once
#include <SFML/Graphics.hpp>

class Render3D
{
	float screenWidth, screenHeight;

	public:
		Render3D(float, float);
		void draw(sf::RenderWindow&, std::vector<float>, float, float);
		void drawPlayer(sf::RenderWindow&, sf::Vector2f, sf::Vector2f, float, float, float, float, size_t, float);
};