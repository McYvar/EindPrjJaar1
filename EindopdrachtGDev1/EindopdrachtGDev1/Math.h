#pragma once

#include "Vector2.h"

class Math {
private:

public:
	static float Abs(float a);
	static float sqrt(float a);
	static float pow(float base, float exp);
	static float random(float rangeMin, float rangeMax);
};