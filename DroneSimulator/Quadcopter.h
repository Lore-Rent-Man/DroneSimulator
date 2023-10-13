#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>
#include <list>
#include "Motor.h"
#include "Line.h"
#include "Circle.h"
#include <octree_code/octree.h>

using namespace std;

class Quadcopter
{
private:
	glm::vec3 m_force{};
	glm::vec3 m_torque{};
	float gravity = 9.81;
public:
	float mass = 0.05f; //kg
	float frictionConstant = 0.016f;
	float dragfrictionConstant = 10.0f;
	glm::vec3 position{0.0f, 5.0f, 0.0f};
	glm::quat orientation{0.0f, 0.0f, 0.0f, 1.0f};
	glm::vec3 velocity{};
	glm::vec3 angular_velocity{};
	glm::vec3 acceleration{};
	glm::vec3 angular_acceleration{};
	glm::mat3 inertia{
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	glm::mat4 MVP{};
	pair<int, Motor> motors[4] = {};

	//Lines representing crosssection
	glm::vec3 cross[4] = {
		glm::vec3 { -1, 0, 0 },
		glm::vec3 { 1, 0, 0 },
		glm::vec3 { 0, 0, -1 },
		glm::vec3 { 0, 0, 1 },
	};

	Circle r_motor[4] = {
		Circle(),
		Circle(),
		Circle(),
		Circle()
	};

	Line cr1 = Line(cross[0], cross[1]);
	Line cr2 = Line(cross[2], cross[3]);

	Quadcopter(float k, float b)
	{
		for (int i = 0; i < 4; i++) {
			motors[i] = pair<int, Motor>{ i, Motor(k, b) };
		}
	}

	glm::vec3 calculateThrustVector(glm::vec4 aVel)
	{
		float totalThrust = 0.0f;
		for (int i = 0; i < 4; i++)
		{
			totalThrust += motors[i].second.calcThrust(aVel[i]);
		}
		return glm::vec3{ 0.0f, totalThrust, 0.0f };
	}

	glm::vec3 calculateTorqueVector(glm::vec4 aVel)
	{
		float torque_x = glm::length(cross[0]) * motors[0].second.calcThrust(aVel[0]) - glm::length(cross[2]) * motors[2].second.calcThrust(aVel[2]);
		float torque_z = glm::length(cross[1]) * motors[1].second.calcThrust(aVel[1]) - glm::length(cross[3]) * motors[3].second.calcThrust(aVel[3]);
		float torque_y = 0;
		for (int i = 0; i < 4; i++)
		{
			torque_y += motors[i].second.calcTorque(aVel[i]);
		}
		return glm::vec3{ torque_x, torque_y, torque_z };
	}

	glm::vec3 calculateAcceleration(glm::vec4 aVel)
	{
		glm::vec3 g { 0.0f, -gravity, 0.0f };
		glm::vec3 f = -velocity * frictionConstant;
		glm::vec3 T = glm::mat3_cast(orientation) * calculateThrustVector(aVel);
		return g - 1 / mass * T + f;
	}

	glm::vec3 calculateAngularAcceleration(glm::vec4 aVel)
	{
		glm::vec3 torque = calculateTorqueVector(aVel);
		glm::vec3 drag = angular_velocity * dragfrictionConstant;
		return glm::inverse(inertia) * (torque - glm::cross(angular_velocity, inertia * angular_velocity)) - drag;
	}

	glm::mat4 update(glm::vec4 input, float dt)
	{
		glm::vec3 a = calculateAcceleration(input);
		glm::vec3 anga = calculateAngularAcceleration(input);

		angular_velocity += anga * dt;
		glm::quat time_derivative = glm::quat(angular_velocity);
		orientation = orientation * time_derivative;
		velocity += dt * a;
		position += dt * velocity;

		glm::mat4 rotation = glm::mat4_cast(orientation);
		glm::mat4 translation = glm::translate(glm::mat4(1.0f), position);
		return translation * rotation;
	}

	void setMVP(glm::mat4 mvp)
	{
		MVP = mvp;
		cr1.setMVP(MVP);
		cr2.setMVP(MVP);
		for (int i = 0; i < 4; i++)
		{
			r_motor[i].setMVP(mvp * glm::translate(glm::mat4(1.0), cross[i]));
		}
	}

	void setColor(glm::vec3 color)
	{
		cr1.setColor(color);
		cr2.setColor(color);
	}

	void drawQuadcopter()
	{
		cr1.draw();
		cr2.draw();
		for (int i = 0; i < 4; i++)
		{
			r_motor[i].draw();
		}
	}
};

