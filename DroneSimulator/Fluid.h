#pragma once

#include <octree_code/octree.h>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Shader.h"
#include "DoubleFBO.h"

using namespace std;
using namespace glm;

class Fluid
{
private:
    
public:

	Fluid(int lx, int ly, int lz);
	DoubleFBO* velocity;
	DoubleFBO* pressure;

	void Advection() {

	}

	void ViscousDiffusion() {

	}
};

