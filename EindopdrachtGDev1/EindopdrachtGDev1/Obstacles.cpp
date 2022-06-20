#include "Obstacles.h"
#include <iostream>

Obstacles::Obstacles(Vector2 pos, float speed, std::string textureName, const float& time, Vector2 direction)
	: Physics(pos, speed, textureName, time),
	direction(direction)
{
	this->hasFlipped = false;
}


Obstacles::~Obstacles()
{
}


Vector2 Obstacles::GetDirection()
{
	return this->direction;
}


void Obstacles::SetDirection(Vector2 newDirection)
{
	this->direction = newDirection;
}


bool Obstacles::checkForColission(std::shared_ptr<Player> player)
{
	if (this->getPosition().y < player->getBottomRightPosition().y
		&& this->getBottomRightPosition().y > player->getPosition().y) {
		if (this->getPosition().x < player->getBottomRightPosition().x
			&& this->getBottomRightPosition().x > player->getPosition().x) {
			return true;
		}
	}
	return false;
}

void Obstacles::UpdateValues(std::shared_ptr<sf::RenderWindow> window, const float& dt)
{
	Physics::UpdateValues(window, dt);
	// Turn around when hitting the edge of the road
	if (getPosition().x < 70 || getPosition().x > window->getSize().x - 70 && !this->hasFlipped) {
		this->direction = Vector2(-this->direction.x, this->direction.y);
		this->hasFlipped = true;
	}
	this->AddForce(this->getCurrentVelocity(), this->GetDirection(), this->getMovementspeed());
	this->Move(Vector2::addUp(this->getCurrentVelocity(), this->GetDirection()), this->getCurrentTime(), dt);
}