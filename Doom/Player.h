#pragma once
#include <SFML/Graphics.hpp>

class Player
{
	
	sf::Texture texture = sf::Texture("Assets\\sprite.png");
	sf::Sprite sprite = sf::Sprite(texture);
	sf::Angle rotation;
	float speed = 0.2f, rotationSpeed = 3.f;
	public:
		Player();
		void Movement();
		sf::Sprite& getSprite() { return sprite; }
		

};