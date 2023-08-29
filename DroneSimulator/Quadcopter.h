#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
class Quadcopter
{
private:
	glm::vec3 m_force{};
	glm::vec3 m_torque{};

public:
	float mass = 1.0f;
	glm::vec3 position{};
	glm::quat orientation{};
	glm::vec3 velocity{};
	glm::vec3 angular_velocity{};
	glm::mat3 inertia{};
	glm::mat3 inverse_inertia{};
};

