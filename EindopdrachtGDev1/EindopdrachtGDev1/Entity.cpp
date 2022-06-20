#include "Entity.h"

Entity::Entity(Vector2 pos, float speed, std::string textureName)
	: movementSpeed(speed),
	textureName(textureName)
{
	this->setTexture(textureName);
	this->setPosition(pos);
}

Entity::~Entity()
{
}


void Entity::setPosition(Vector2 newPos)
{
	this->sprite.setPosition(newPos.toSFVector2());
	postition = newPos;
}


Vector2 Entity::getPosition()
{
	return this->postition;
}


void Entity::setMovementspeed(float newSpeed)
{
	this->movementSpeed = newSpeed;
}


float Entity::getMovementspeed()
{
	return this->movementSpeed;
}


void Entity::setTexture(std::string textureName)
{
	this->texture.loadFromFile("assets/" + textureName + ".png");
	this->sprite.setTexture(this->texture);
}


Vector2 Entity::getBottomRightPosition()
{
	sf::FloatRect tempRect = this->sprite.getLocalBounds();
	Vector2 size(tempRect.left + tempRect.width, tempRect.top + tempRect.height);
	return Vector2::addUp(this->getPosition(), size);
}

sf::Sprite& Entity::getSprite()
{
	return this->sprite;
}

std::string Entity::getTextureName()
{
	return textureName;
}


void Entity::Render(std::shared_ptr<sf::RenderWindow> window)
{
	window->draw(this->getSprite());
}
