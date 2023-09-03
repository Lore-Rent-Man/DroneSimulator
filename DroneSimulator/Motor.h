#pragma once

#include <math.h>

class Motor
{
private:

	float baseCurrent;
	float kTor; //Torque proportionality constant
	float kBla; //Blade configuration constant
	float kVol; //Back-emf per rpm
	float A;	//Area swept out under rotor
	float PA; //Propeller cross-section
	float Cd; //Dimensionless constant
	float Radius;

public:

	float inputCurrent;
	int motorNumber;

	float calculateAngularVelocity() {
		return 0.0;
	}

	float calculateTorque()
	{
		return kTor * (inputCurrent - baseCurrent);
	}

	float calculatePower(double aVel)
	{
		return kVol / kTor * calculateTorque() * aVel;
	}

	float calculateThrust(float p, float aVel) {
		return pow((kVol * kBla * sqrt(2 * p * A)) / kTor * calculateAngularVelocity(), 2);
	}

	float calculateTorqueDrag(float p, float aVel) {
		return 0.5 * Radius * p * Cd * A * (aVel * Radius);
	}
};

