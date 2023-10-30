#include "Fluid.h"

Fluid::Fluid(int lx, int ly, int lz) {
	velocity = new DoubleFBO(lx, ly, lz, GL_RGB, GL_RGB, GL_FLOAT, GL_LINEAR);
	pressure = new DoubleFBO(lx, ly, lz, GL_RG, GL_RG, GL_FLOAT, GL_LINEAR);
}