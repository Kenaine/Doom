#pragma once
#include <SFML/Graphics.hpp>

class Player
{
	
	sf::Texture texture = sf::Texture("Assets/sprite.png");
	sf::Sprite sprite = sf::Sprite(texture);
	sf::Angle rotation = sf::degrees(180.f);
	float speed = 3.0f, rotationSpeed = 0.8f;

	float degreesToRadians(float);
	private:
		bool isCollidingWithWalls(const sf::Vector2f& newPosition);

	public:
		Player();
		void Movement();
		sf::Sprite& getSprite() { return sprite; }
		

};