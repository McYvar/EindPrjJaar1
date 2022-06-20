#include "Vector2.h"
#include "Math.h"

Vector2::Vector2() {
    this->x = 0;
    this->y = 0;
}

Vector2::Vector2(float x, float y) {
    this->x = x;
    this->y = y;
    this->magnitude = getMagnitude();
}

Vector2::~Vector2()
{
}

float Vector2::getMagnitude()
{
    return std::sqrt(this->x*this->x + this->y*this->y);
}

sf::Vector2f Vector2::toSFVector2()
{
    return sf::Vector2f(this->x, this->y);
}

float Vector2::Distance(Vector2 a, Vector2 b)
{
    return Vector2(b.x - a.x, b.y - a.y).getMagnitude();
}

std::string Vector2::toString()
{
    return "Vector2(" + std::to_string(this->x) + ", " + std::to_string(this->y) + ")";
}

Vector2 Vector2::addUp(Vector2 a, Vector2 b)
{
    return Vector2(a.x + b.x, a.y + b.y);
}

Vector2 Vector2::getNormalized(Vector2 a)
{
    float tempLength = a.getMagnitude();
    return Vector2(a.x / tempLength, a.y / tempLength);
}

Vector2 Vector2::subtract(Vector2 a, Vector2 b)
{
    return Vector2(b.x - a.x, b.y - a.y);
}

Vector2 Vector2::getReversed(Vector2 a)
{
    return Vector2(-a.x, -a.y);
}

Vector2 Vector2::toVector2(sf::Vector2f a)
{
    return Vector2(a.x, a.y);
}
