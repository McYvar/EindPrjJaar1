#include "Math.h"
#include <random>

float Math::Abs(float a) {
	return sqrt(pow(a, 2.f));
}

float Math::sqrt(float a)
{
	return pow(a, 0.5f);
}

float Math::pow(float base, float exp)
{
	return std::pow(base, exp);
}

float Math::random(float rangeMin, float rangeMax)
{
	std::random_device rd;
	std::mt19937 e2(rd());
	std::uniform_real_distribution<> dist(rangeMin, rangeMax);
	return dist(e2);
}
