#pragma once
#include "Physics.h"
#include "Player.h"

class Obstacles : public Physics
{
private:
	Vector2 direction;
	bool hasFlipped = false;
public:
	Obstacles(Vector2 pos, float speed, std::string textureName, const float& time, Vector2 direction);
	~Obstacles();

	Vector2 GetDirection();
	void SetDirection(Vector2 newDirection);

	// collision bool
	bool checkForColission(std::shared_ptr<Player> player);

	void UpdateValues(std::shared_ptr<sf::RenderWindow> window, const float& dt);
};