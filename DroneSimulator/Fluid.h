#pragma once

#include <octree_code/octree.h>

class Fluid
{
private:
	Octree<double>* o;

public:
	Fluid(float size, int resolution) {
		o = new Octree<double>(resolution);
	}

	void Advection() {

	}

	void ViscousDiffusion() {

	}
};

