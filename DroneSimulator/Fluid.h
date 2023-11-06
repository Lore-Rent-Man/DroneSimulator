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
	Shader advectionShader = Shader("basefluidvertexshader.glsl", "advectionfragmentshader.glsl");
	Shader divergenceShader = Shader("basefluidvertexshader.glsl", "divergencefragmentshader.glsl");
	Shader pressureShader = Shader("basefluidvertexshader.glsl", "pressurefragmentshader.glsl");
	Shader gradientSubtractShader = Shader("basefluidvertexshader.glsl", "gradientfragmentshader.glsl");
	Shader clearShader = Shader("basefluidvertexshader.glsl", "clearfragmentshader.glsl");

	unsigned int blitBuffer, vao;
	int lx, ly, lz;

public:
	DoubleFBO* velocity;
	DoubleFBO* pressure;
	FBO* divergence;

	Fluid(int lx, int ly, int lz);

	void step(float deltaTime);

	void blit(FBO* target, bool clear = false);
};

