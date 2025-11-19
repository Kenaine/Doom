#include <SFML/Graphics.hpp>
#include "Player.h"

Player::Player()
{
	sprite.setPosition(sf::Vector2f(960.f, 540.f));
	sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2.f, texture.getSize().y / 2.f));
}

void Player::Movement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		sprite.move(sf::Vector2f(0.f, -speed));
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		sprite.move(sf::Vector2f(0.f, speed));


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		sprite.move(sf::Vector2f(-speed, 0.f));
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		sprite.move(sf::Vector2f(speed, 0.f));

}