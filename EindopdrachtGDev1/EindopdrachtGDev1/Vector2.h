#pragma once

#include <SFML/Graphics.hpp>

class Vector2
{
private:
	float magnitude;

public:
	float x;
	float y;
	Vector2();
	Vector2(float x, float y);
	~Vector2();
	float getMagnitude();
	sf::Vector2f toSFVector2();
	static float Distance(Vector2 a, Vector2 b);
	std::string toString();
	static Vector2 addUp(Vector2 a, Vector2 b);
	static Vector2 subtract(Vector2 a, Vector2 b);
	static Vector2 getNormalized(Vector2 a);
	static Vector2 getReversed(Vector2 a);
	static Vector2 toVector2(sf::Vector2f a);
};