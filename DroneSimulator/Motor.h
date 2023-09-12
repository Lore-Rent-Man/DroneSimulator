#pragma once

#include <math.h>

class Motor
{
private:

	float k;
	float b;

public:

	Motor()
	{
		this->k = 0;
		this->b = 0;
	}

	Motor(float k, float b)
	{
		this->k = k;
		this->b = b;
	}

	float calcThrust(float aVel)
	{
		return k * pow(aVel, 2);
	}

	float calcTorque(float aVel)
	{
		return b * pow(aVel, 2);
	}
};

