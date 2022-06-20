#include "Player.h"
#include <iostream>

Player::Player(Vector2 pos, float speed, std::string textureName, const float& time, int lives, float friction)
	: Physics(pos, speed, textureName, time),
	lives(lives)
{
	this->setFriction(friction);
}

Player::~Player()
{
}

int Player::getLives()
{
	return this->lives;
}

void Player::removeLife()
{
	this->lives -= 1;
}

bool Player::leftIsPressed()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::A);
}

bool Player::rightIsPressed()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::D);
}

void Player::UpdateValues(std::shared_ptr<sf::RenderWindow> window, const float& dt)
{
	Physics::UpdateValues(window, dt);

	// Player input
	if (leftIsPressed() && this->getPosition().x > 70) AddForce(getCurrentVelocity(), Vector2(-1.f, 0.f), getMovementspeed());
	if (this->getPosition().x < 70) {
		this->setPosition(Vector2(70.1f, this->getPosition().y));
		this->setCurrentVelocity(Vector2(0, 0));
	}

	if (rightIsPressed() && this->getBottomRightPosition().x < window->getSize().x - 70)  AddForce(getCurrentVelocity(), Vector2(1.f, 0.f), getMovementspeed());
	if (this->getBottomRightPosition().x > window->getSize().x - 70) {
		this->setPosition(Vector2(window->getSize().x - (70.1f + Vector2::subtract(this->getPosition(), this->getBottomRightPosition()).x), this->getPosition().y));
		this->setCurrentVelocity(Vector2(0, 0));
	}
	
	this->CounterVelocity(this->getCurrentVelocity(), this->getFriction());

	this->Move(getCurrentVelocity(), 1, dt);
}