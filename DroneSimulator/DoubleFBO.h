#pragma once

#include "Shader.h"
#include "FBO.h"

class DoubleFBO
{
private:
	FBO* fbo1;
	FBO* fbo2;
public:
	float texelSizeX, texelSizeY, texelSizeZ;

	DoubleFBO(int lx, int ly, int lz, GLint interalFormat, GLint format, GLint type, GLint param);
	FBO* read();
	void read(FBO* value);
	FBO* write();
	void write(FBO* value);
	void swap();
};

