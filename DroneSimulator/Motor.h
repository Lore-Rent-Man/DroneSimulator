#include <math.h>

#pragma once
class Motor
{
public:
	double inputCurrent;
	double baseCurrent;
	double kTor; //Torque proportionality constant
	double kBla; //Blade configuration constant
	double kVol; //Back-emf per rpm
	double A;	//Area swept out under rotor

	double calculateAngularVelocity() {
		return 0.0;
	}

	double calculateTorque()
	{
		return kTor * (inputCurrent - baseCurrent);
	}

	double calculatePower(double aVel)
	{
		return kVol / kTor * calculateTorque() * aVel;
	}

	double calculateThrust(double p, double aVel) {
		return pow((kVol * kBla * sqrt(2 * p * A)) / kTor * calculateAngularVelocity(), 2);
	}


};

