#pragma once

#include "Physics.h"

class Player : public Physics
{
private:
	int lives;
public:
	Player(Vector2 pos, float speed, std::string textureName, const float& time, int lives, float friction);
	~Player();

	int getLives();
	void removeLife();
	bool leftIsPressed();
	bool rightIsPressed();

	void UpdateValues(std::shared_ptr<sf::RenderWindow> window, const float& dt);
};

