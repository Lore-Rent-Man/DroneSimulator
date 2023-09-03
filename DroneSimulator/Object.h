#pragma once

#include <glm/glm.hpp>
#include <vector>

using namespace std;

class Object {
protected:
	glm::mat4 MVP;
	glm::vec3 color;
	vector<float> vertices;

public: 
	virtual void draw() {};

	void setColor(glm::vec3 c)
	{
		color = c;
	}

	void setMVP(glm::mat4 m)
	{
		MVP = m;
	}
};