#include "FBO.h"

FBO::FBO(int lx, int ly, int lz, GLint interalFormat, GLint format, GLint type, GLint param)
{
	this->lx = lx;
	this->ly = ly;
	this->lz = lz;

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_3D, texture);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, param);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, param);
	glTexImage3D(GL_TEXTURE_3D, 0, interalFormat, lx, ly, lz, 0, format, type, NULL);

	this->texelSizeX = 1.0 / lx;
	this->texelSizeY = 1.0 / ly;
	this->texelSizeZ = 1.0 / lz;

	glGenFramebuffers(1, &this->ID);
	glBindFramebuffer(GL_FRAMEBUFFER, this->ID);
	glFramebufferTexture3D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_3D, this->texture, 0, 0);
	glViewport(0, 0, lx, ly);
	glClear(GL_COLOR_BUFFER_BIT);
}

unsigned int FBO::attach(unsigned int id) {
	glActiveTexture(GL_TEXTURE0 + id);
	glBindTexture(GL_TEXTURE_3D, texture);
	return id;
}

FBO::~FBO()
{
	glDeleteTextures(1, &texture);
	glDeleteFramebuffers(1, &ID);
}
