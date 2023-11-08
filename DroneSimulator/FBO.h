#pragma once

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

using namespace std;
using namespace glm;

class FBO
{
public:
	unsigned int texture, ID;
	float texelSizeX, texelSizeY, texelSizeZ;
	int lx, ly, lz;

	FBO(int lx, int ly, int lz, GLint interalFormat, GLint format, GLint type, GLint param);
	unsigned int attach(unsigned int id);
	~FBO();
};

