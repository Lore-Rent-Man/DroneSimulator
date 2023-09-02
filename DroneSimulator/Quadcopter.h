#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <list>
#include "Motor.h"

using namespace std;

class Quadcopter
{
private:
	glm::vec3 m_force{};
	glm::vec3 m_torque{};

public:
	double mass = 1.0f;
	glm::vec3 position{};
	glm::quat orientation{};
	glm::vec3 velocity{};
	glm::vec3 angular_velocity{};
	
	pair<int, Motor> motors[4] = {};

	glm::vec3 calculateFriction(float frictionConstant)
	{
		return -frictionConstant * velocity;
	}

	glm::vec3 updateTorque(float p, float aVel)
	{
		glm::vec3 u_torque{};
		for (int i = 0; i < 4; i++) {
			u_torque[0] += motors[i].second.calculateThrust(p, aVel) * motors[i].first;
			u_torque[1] += motors[i].second.calculateThrust(p, aVel) * motors[i].first;
			u_torque[2] += motors[i].second.calculateTorqueDrag(p, aVel);
		}
	}
};

