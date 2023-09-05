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

public:
	double mass = 1.0f;
	glm::vec3 position{};
	glm::quat orientation{};
	glm::vec3 velocity{};
	glm::vec3 angular_velocity{};
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

