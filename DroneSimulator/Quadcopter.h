#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
class Quadcopter
{
private:
	glm::dvec3 m_force{};
	glm::dvec3 m_torque{};

public:
	double mass = 1.0f;
	glm::dvec3 position{};
	glm::quat orientation{};
	glm::dvec3 velocity{};
	glm::dvec3 angular_velocity{};

	glm::dvec3 calculateFriction(double frictionConstant)
	{
		return -frictionConstant * velocity;
	}


};

