#pragma once

#include "Entity.h"

class Physics : public Entity
{
private:
	Vector2 currentPosition = Vector2();
	Vector2 lastFramePosition = Vector2();
	Vector2 currentVelocity = Vector2();

	float time = 0;
	float friction = 1;

	bool firstFrameVelocitySet = false;

public:
	Physics(Vector2 pos, float speed, std::string textureName, const float& time);
	~Physics();

	float getFriction();
	void setFriction(float friction);
	Vector2& getCurrentVelocity();
	void setCurrentVelocity(Vector2 newVel);
	float getCurrentTime();

	void Move(Vector2 currentVelocity, const float& time, const float& dt);

	virtual void UpdateValues(std::shared_ptr<sf::RenderWindow> window, const float& dt);

	Vector2 Velocity(Vector2 currentPosition, Vector2 lastFramePosition, const float& dt);
	void AddForce(Vector2& currentVelocity, Vector2 directionNormalized, float speed);

	void CounterVelocity(Vector2& currentVelocity, float friction);
};

