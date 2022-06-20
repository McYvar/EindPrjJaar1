#pragma once

#include <SFML/Graphics.hpp>
#include "Math.h"

class Entity
{
private:
	Vector2 postition;
	float movementSpeed = 0;
	sf::Sprite sprite;
	sf::Texture texture;
	std::string textureName;

public:
	// Construct / Destruct
	Entity(Vector2 pos, float speed, std::string textureName);
	virtual ~Entity();

	// Functions
	void setPosition(Vector2 newPos);
	Vector2 getPosition();
	void setMovementspeed(float newSpeed);
	float getMovementspeed();
	void setTexture(std::string textureName);
	Vector2 getBottomRightPosition(); // For colission
	sf::Sprite& getSprite();
	std::string getTextureName();

	virtual void UpdateValues(std::shared_ptr<sf::RenderWindow> window, const float& dt) = 0;
	void Render(std::shared_ptr<sf::RenderWindow> window);
};

