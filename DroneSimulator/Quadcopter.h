#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <list>
#include "Motor.h"
#include "Line.h"
#include "Circle.h"

using namespace std;

class Quadcopter
{
private:
	glm::vec3 m_force{};
	glm::vec3 m_torque{};
	float gravity = 9.81;
public:
	float mass = 1.0f;
	float frictionConstant = 0.016f;
	glm::vec3 position{};
	glm::quat orientation{};
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
		float torque_y = glm::length(cross[1]) * motors[1].second.calcThrust(aVel[1]) - glm::length(cross[3]) * motors[3].second.calcThrust(aVel[3]);
		float torque_z = 0;
		for (int i = 0; i < 4; i++)
		{
			torque_z += motors[i].second.calcTorque(aVel[i]);
		}
	}

	glm::vec3 calculateAcceleration(glm::vec4 aVel)
	{
		glm::vec3 g { 0.0f, -gravity, 0.0f };
		glm::vec3 f = velocity * frictionConstant;
		glm::vec3 T = glm::mat3_cast(orientation) * calculateThrustVector(aVel);
		return g + 1 / mass * T + f;
	}

	glm::vec3 AngularVelocityToTimeDerivative(glm::vec3 a)
	{
		glm::vec3 euler_angles = glm::eulerAngles(orientation);
		float phi = euler_angles[0];
		float theta = euler_angles[1];
		float psi = euler_angles[2];
		glm::mat3 W{
			1.0f, 0.0f, -sin(theta),
			0.0f, cos(phi), cos(theta) * sin(phi),
			0.0f, -sin(phi), cos(theta) * cos(phi)
		};
		return glm::inverse(W) * a;
	}

	glm::vec3 TimeDerivativeToAngularVelocity(glm::vec3 t)
	{
		glm::vec3 euler_angles = glm::eulerAngles(orientation);
		float phi = euler_angles[0];
		float theta = euler_angles[1];
		float psi = euler_angles[2];
		glm::mat3 W{
			1.0f, 0.0f, -sin(theta),
			0.0f, cos(phi), cos(theta) * sin(phi),
			0.0f, -sin(phi), cos(theta) * cos(phi)
		};
		return W * t;
	}

	glm::vec3 calculateAngularAcceleration(glm::vec4 aVel)
	{
		glm::vec3 torque = calculateTorqueVector(aVel);
		return glm::inverse(inertia) * (torque - glm::cross(angular_velocity, inertia * angular_velocity));
	}

	void update(glm::vec4 input, float dt)
	{
		glm::vec3 a = calculateAcceleration(input);
		glm::vec3 anga = calculateAngularAcceleration(input);

		angular_velocity += anga * dt;
		glm::vec3 time_derivative = AngularVelocityToTimeDerivative(angular_velocity);
		orientation = orientation * time_derivative;
		velocity += dt * a;
		position += dt * velocity;
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

