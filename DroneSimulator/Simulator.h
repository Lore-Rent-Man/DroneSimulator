#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <cstdlib>
#include "Quadcopter.h"

class Simulator
{
private:
	float dt = 0.005;
	float deviation = 100;
	glm::vec3 aVel{};

public:
	void Initialize() {
		aVel[0] = 2 * deviation * (((double)rand() / (RAND_MAX)) + 1) - deviation;
		aVel[1] = 2 * deviation * (((double)rand() / (RAND_MAX)) + 1) - deviation;
		aVel[2] = 2 * deviation * (((double)rand() / (RAND_MAX)) + 1) - deviation;
	}

	void Start() {
		
	}

	glm::vec3 thetadot2omega(glm::vec3 aVel, glm::vec3 angles)
	{
		int phi = angles[0];
		int the = angles[1];
		int psi = angles[3];
		glm::mat3x3 W{
			1.0, 0.0,-sin(the),
			0.0, cos(phi), cos(the) * sin(phi),
			0.0, -sin(phi), cos(the) * cos(phi)
		};
		return W * aVel;
	}
};

