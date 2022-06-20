#include "Physics.h"
#include <iostream>

Physics::Physics(Vector2 pos, float speed, std::string textureName, const float& time)
	: Entity(pos, speed, textureName),
	time(time)
{
}

Physics::~Physics()
{
}

float Physics::getFriction()
{
	return this->friction;
}

void Physics::setFriction(float friction)
{
	this->friction = friction;
}

Vector2& Physics::getCurrentVelocity()
{
	return currentVelocity;
}

void Physics::setCurrentVelocity(Vector2 newVel)
{
	this->currentVelocity = newVel;
}

float Physics::getCurrentTime()
{
	return this->time;
}

void Physics::Move(Vector2 currentVelocity, const float& time, const float& dt)
{
	this->setPosition(Vector2(this->getPosition().x + currentVelocity.x * time * dt,
		this->getPosition().y + currentVelocity.y * time * dt));
}

void Physics::UpdateValues(std::shared_ptr<sf::RenderWindow> window, const float& dt)
{
	this->lastFramePosition = this->currentPosition;
	currentPosition = this->getPosition();
	this->currentVelocity = Velocity(this->currentPosition, this->lastFramePosition, dt);

	this->time += dt / 100;
	if (!this->firstFrameVelocitySet) {
		currentVelocity = Vector2(0, 0);
		this->firstFrameVelocitySet = true;
	}
}

Vector2 Physics::Velocity(Vector2 currentPosition, Vector2 lastFramePosition, const float& dt) {
	float tempX = (currentPosition.x - lastFramePosition.x) / dt;
	float tempY = (currentPosition.y - lastFramePosition.y) / dt;
	return Vector2(tempX, tempY);
}

void Physics::AddForce(Vector2& currentVelocity, Vector2 directionNormalized, float speed)
{
	Vector2 direction = Vector2::getNormalized(directionNormalized);
	direction = Vector2(direction.x * speed, direction.y * speed);
	currentVelocity = Vector2::addUp(currentVelocity, direction);
}

void Physics::CounterVelocity(Vector2& currentVelocity, float friction)
{
	Vector2 counterVector = Vector2::getReversed(currentVelocity);
	currentVelocity = Vector2(currentVelocity.x + counterVector.x * friction, currentVelocity.y + counterVector.y * friction);
}
