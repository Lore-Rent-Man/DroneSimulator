#include "DoubleFBO.h"

DoubleFBO::DoubleFBO(int lx, int ly, int lz, GLint interalFormat, GLint format, GLint type, GLint param)
{
	fbo1 = new FBO(lx, ly, lz, interalFormat, format, type, param);
	fbo2 = new FBO(lx, ly, lz, interalFormat, format, type, param);
	texelSizeX = fbo1->texelSizeX;
	texelSizeY = fbo1->texelSizeY;
	texelSizeZ = fbo1->texelSizeZ;
}

FBO* DoubleFBO::read()
{
	return fbo1;
}

void DoubleFBO::read(FBO* value)
{
	fbo1 = value;
}

FBO* DoubleFBO::write()
{
	return fbo2;
}

void DoubleFBO::write(FBO* value)
{
	fbo2 = value;
}

void DoubleFBO::swap()
{
	std::swap(fbo1, fbo2);
}