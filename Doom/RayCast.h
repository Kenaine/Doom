#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <vector>
#include <tuple>

class RayCast
{
	Player& player;
	std::vector<sf::VertexArray> objects;
	sf::VertexArray fan;
	std::vector<float> distances;
	float maxDistance = 500.f;
	int vertexCount = 480;

	sf::Vector2f findIntersectionPoint(sf::Vector2f, sf::Vector2f, float&);

	bool checkIntersection(float[3], float[3], sf::Vector2f&);
	void twoPointToLine(sf::Vector2f, sf::Vector2f, float&, float&, float&);
	void iterateRay(int, int, float, float, sf::Vector2f);
	public:
		RayCast(Player&, std::vector<sf::VertexArray>);
		void update();
		void draw(sf::RenderWindow& window) { window.draw(fan); }
		std::vector<float>& getDistances() { return distances; }
};