#pragma once
#include "Physics.h"

class Background : public Physics
{
public:
	Background(Vector2 pos, float speed, std::string textureName, const float& time);
	~Background();

	void UpdateValues(std::shared_ptr<sf::RenderWindow> window, const float& dt);
};

