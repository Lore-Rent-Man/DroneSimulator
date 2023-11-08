#include "Fluid.h"

#define PRESSURE_VALUE 0.8
#define PRESSURE_ITERATIONS 20
#define VELOCITY_DISSIPATION 0.2
#define DENSITY_DISSIPATION 1
#define SPLAT_RADIUS 1.0
#define SPLAT_FORCE 6000

Fluid::Fluid(int lx, int ly, int lz, int width, int height) {

	this->lx = lx;
	this->ly = ly;
	this->lz = lz;
	this->width = width;
	this->height = height;
	this->aspectRatio = float(this->width) / height;

	dye = new DoubleFBO(1024, 1024, lz, GL_RGBA, GL_RGBA, GL_FLOAT, GL_LINEAR);
	velocity = new DoubleFBO(256, 256, lz, GL_RGB16F, GL_RGB, GL_FLOAT, GL_LINEAR);
	pressure = new DoubleFBO(256, 256, lz, GL_RG, GL_RG, GL_FLOAT, GL_NEAREST);
	divergence = new FBO(256, 256, lz, GL_RED, GL_RED, GL_FLOAT, GL_NEAREST);
	
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

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Fluid::splat(splatPointer p) {

	float x = p.texcoordX;
	float y = p.texcoordY;
	float dx = p.deltaX * SPLAT_FORCE;
	float dy = p.deltaY * SPLAT_FORCE;


	glm::vec3 color = p.color;

	splatShader.use();
	splatShader.setInt("uTarget", velocity->read()->attach(0));
	splatShader.setFloat("aspectRatio", aspectRatio);
	splatShader.setVec3("point", glm::vec3{ x, y, 0.0f });
	splatShader.setVec3("color", dx, dy, 0.0);
	splatShader.setFloat("radius", SPLAT_RADIUS/100.0f * aspectRatio);
	blit(velocity->write());
	velocity->swap();

	splatShader.setInt("uTarget", dye->read()->attach(0));
	splatShader.setVec3("color", color);
	blit(dye->write());
	dye->swap();
}

void Fluid::step(float deltaTime) {
	glDisable(GL_BLEND);

	glm::vec3 texelSize(velocity->texelSizeX, velocity->texelSizeY, velocity->texelSizeZ);

	/*divergenceShader.use();
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
	velocity->swap();*/

	advectionShader.use();
	advectionShader.setVec3("texelSize", texelSize);
	unsigned int velocityId = velocity->read()->attach(0);
	advectionShader.setInt("uVelocity", velocityId);
	advectionShader.setInt("uSource", velocityId);
	advectionShader.setFloat("dt", deltaTime);
	advectionShader.setFloat("dissipation", VELOCITY_DISSIPATION);
	blit(velocity->write());
	velocity->swap();

	advectionShader.setInt("uVelocity", velocity->read()->attach(0));
	advectionShader.setInt("uSource", dye->read()->attach(1));
	advectionShader.setFloat("dissipation", DENSITY_DISSIPATION);
	blit(dye->write());
	dye->swap();
}

void Fluid::render() {
	glEnable(GL_BLEND);
	displayShader.use();
	displayShader.setInt("uVelocity", dye->read()->attach(0));
	blit(NULL);
}

void Fluid::blit(FBO* target, bool clear) {
	if (target == NULL)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, width, height);
	}
	else
	{
		glBindFramebuffer(GL_FRAMEBUFFER, target->ID);
		glViewport(0, 0, target->lx, target->ly);
	}
	if (clear)
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 6 * lz);
}

Fluid::~Fluid() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &blitBuffer);
}



