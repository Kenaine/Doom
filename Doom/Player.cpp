#include <SFML/Graphics.hpp>
#include "Player.h"
#include <cmath>
#include <filesystem>

Player::Player()
{
	std::string path = "Assets/sprite.png";
#ifdef _WIN32
    path = "Assets\\sprite.png";
#endif

	if (!texture.loadFromFile(path)) {
		// error handling
	}

	sprite.setPosition(sf::Vector2f(960.f, 540.f));
	sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2.f, texture.getSize().y / 2.f));
	sprite.setRotation(rotation);
}

void Player::Movement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		float xVector = std::cos(degreesToRadians(rotation.asDegrees())) * speed;
		float yVector = std::sin(degreesToRadians(rotation.asDegrees())) * speed;

		sprite.move(sf::Vector2f(xVector, yVector));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		float xVector = std::cos(degreesToRadians(rotation.asDegrees())) * speed;
		float yVector = std::sin(degreesToRadians(rotation.asDegrees())) * speed;
		sprite.move(sf::Vector2f(-xVector, -yVector));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		rotation -= sf::degrees(rotationSpeed);
		sprite.setRotation(rotation);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		rotation += sf::degrees(rotationSpeed);
		sprite.setRotation(rotation);
	}

}

float Player::degreesToRadians(float degrees)
{
	return degrees * 3.14159265359f / 180.f;
}