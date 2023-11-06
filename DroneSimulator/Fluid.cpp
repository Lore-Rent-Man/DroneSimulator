#include "Fluid.h"

#define PRESSURE_VALUE 0.8
#define PRESSURE_ITERATIONS 20
#define VELOCITY_DISSIPATION 0.2

Fluid::Fluid(int lx, int ly, int lz) {

	this->lx = lx;
	this->ly = ly;
	this->lz = lz;

	velocity = new DoubleFBO(lx, ly, lz, GL_RGB, GL_RGB, GL_FLOAT, GL_LINEAR);
	pressure = new DoubleFBO(lx, ly, lz, GL_RG, GL_RG, GL_FLOAT, GL_LINEAR);
	divergence = new FBO(lx, ly, lz, GL_RED, GL_RED, GL_FLOAT, GL_LINEAR);
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &blitBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, blitBuffer);
	vector<float> vertices;
	for (float i = 0.0; i < 1.0; i += (1.0/lz))
	{
		vertices.insert(vertices.end(),
			{
				-1, -1, i,
				-1, 1, i,
				1, 1, i,
				-1, -1, i,
				1, 1, i,
				1, -1, i
			});
	}
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void Fluid::step(float deltaTime) {
	glDisable(GL_BLEND);

	glm::vec3 texelSize(velocity->texelSizeX, velocity->texelSizeY, velocity->texelSizeZ);

	divergenceShader.use();
	divergenceShader.setVec3("texelSize", texelSize);
	divergenceShader.setInt("uVelocity", velocity->read()->attach(0));
	blit(divergence);

	clearShader.use();
	clearShader.setInt("uTexture", pressure->read()->attach(0));
	clearShader.setFloat("value", PRESSURE_VALUE);
	blit(pressure->write());
	pressure->swap();

	pressureShader.use();
	pressureShader.setVec3("texelSize", texelSize);
	pressureShader.setInt("uDivergence", divergence->attach(0));
	for (int i = 0; i < PRESSURE_ITERATIONS; i++)
	{
		pressureShader.setInt("uPressure", pressure->read()->attach(1));
		blit(pressure->write());
		pressure->swap();
	}

	gradientSubtractShader.use();
	gradientSubtractShader.setVec3("texelSize", texelSize);
	gradientSubtractShader.setInt("uPressure", pressure->read()->attach(0));
	gradientSubtractShader.setInt("uVelocity", velocity->read()->attach(1));
	blit(velocity->write());
	velocity->swap();

	advectionShader.use();
	advectionShader.setVec3("texelSize", texelSize);
	advectionShader.setInt("uVelocity", velocity->read()->attach(0));
	advectionShader.setInt("uSource", velocity->read()->attach(0));
	advectionShader.setFloat("dt", deltaTime);
	advectionShader.setFloat("dissipation", VELOCITY_DISSIPATION);
	blit(velocity->write(), true);
	velocity->swap();
}

void Fluid::blit(FBO* target, bool clear) {
	if (target == NULL)
	{
		glViewport(0, 0, GL_RENDERBUFFER_WIDTH, GL_RENDERBUFFER_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, NULL);
	}
	else
	{
		glViewport(0, 0, target->lx, target->ly);
		glBindFramebuffer(GL_FRAMEBUFFER, target->ID);
	}
	if (clear)
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	glDrawArrays(GL_TRIANGLES, 0, 0);
}



