#pragma once

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Object.h"
#include "Line.h"
#include "Shader.h"

class Axes : public Object {
public:

	Line x_axis = Line(glm::vec3{ 0.0, 0.0, 0.0 }, glm::vec3{ 1.0, 0.0, 0.0 });
	Line y_axis = Line(glm::vec3{ 0.0, 0.0, 0.0 }, glm::vec3{ 0.0, 1.0, 0.0 });
	Line z_axis = Line(glm::vec3{ 0.0, 0.0, 0.0 }, glm::vec3{ 0.0, 0.0, 1.0 });

	void setMVP(glm::mat4 mvp)
	{
		MVP = mvp;
		x_axis.setMVP(mvp);
		y_axis.setMVP(mvp);
		z_axis.setMVP(mvp);
	}

    void draw() {
		x_axis.setColor(glm::vec3{ 1.0f, 0.0f, 0.0f });
		y_axis.setColor(glm::vec3{ 0.0f, 1.0f, 0.0f });
		z_axis.setColor(glm::vec3{ 0.0f, 0.0f, 1.0f });
		x_axis.draw();
		y_axis.draw();
		z_axis.draw();
    }
};