#pragma once

#include <octree_code/octree.h>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glm/gtx/string_cast.hpp>

#include <iostream>
#include "Shader.h"
#include "DoubleFBO.h"

using namespace std;
using namespace glm;

struct splatPointer {
	int id = -1;
	float texcoordX = 0;
	float texcoordY = 0;
	float prevTexcoordX = 0;
	float prevTexcoordY = 0;
	float deltaX = 0;
	float deltaY = 0;
	bool down = false;
	bool moved = false;
	glm::vec3 color{ 1.0f, 0.5f, 0.2f };
};

class Fluid
{
	Shader splatShader = Shader("basefluidvertexshader.glsl", "splatfragmentshader.glsl");
	Shader divergenceShader = Shader("basefluidvertexshader.glsl", "divergencefragmentshader.glsl");
	Shader pressureShader = Shader("basefluidvertexshader.glsl", "pressurefragmentshader.glsl");
	Shader gradientSubtractShader = Shader("basefluidvertexshader.glsl", "gradientfragmentshader.glsl");
	Shader clearShader = Shader("basefluidvertexshader.glsl", "clearfragmentshader.glsl");
	Shader displayShader = Shader("basefluidvertexshader.glsl", "displayfragmentshader.glsl");

	unsigned int blitBuffer, vao;
	int lx, ly, lz, width, height, aspectRatio;

public:
	Shader advectionShader = Shader("basefluidvertexshader.glsl", "advectionfragmentshader.glsl");

	DoubleFBO* dye;
	DoubleFBO* velocity;
	DoubleFBO* pressure;
	FBO* divergence;

	Fluid(int lx, int ly, int lz, int width, int height);

	void splat(splatPointer p);

	void advect(float deltaTime);

	void step(float deltaTime);

	void render();

	void blit(FBO* target, bool clear = false);

	~Fluid();
};

