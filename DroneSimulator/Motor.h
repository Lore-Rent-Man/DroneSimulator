#pragma once

#include <math.h>

class Motor
{
private:

	float baseCurrent;
	float k;
	float b;
	float Radius;

public:

	float inputCurrent;
	int motorNumber;

	float calcThrust(float aVel)
	{
		return k * pow(aVel, 2);
	}

	float calcTorque(float aVel)
	{
		return b * pow(aVel, 2);
	}
};

