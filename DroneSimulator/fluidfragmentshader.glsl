#version 330 core

uniform sampler2DRect velocity;
uniform sampler2DRect pressure;

void advect(vec2 coords,
	float timestep, 
	float rdx,
	sampler2DRect u,
	sampler2DRect x,
	out vec4 xNew)
{
	vec2 pos = coords - timestep * rdx * vec2(texture(u, coords));
	xNew = texture(x, pos);
}	

void jacobi(vec2 coords, 
	float alpha,
	float rBeta,
	sampler2DRect x,
	sampler2DRect b,
	out vec4 xNew)
{
	vec4 xL = texture(x, coords - vec2(1, 0));
	vec4 xR = texture(x, coords + vec2(1, 0));
	vec4 xB = texture(x, coords - vec2(0, 1));
	vec4 xT = texture(x, coords + vec2(0, 1));

	vec4 bC = texture(b, coords);

	xNew = (xL + xR + xB + xT + alpha * bC) * rBeta;
}

void divergence(vec2 coords,
	float rdx,
	sampler2DRect w,
	out float div)
{
	vec4 wL = texture(w, coords - vec2(1, 0));
	vec4 wR = texture(w, coords + vec2(1, 0));
	vec4 wB = texture(w, coords - vec2(0, 1));
	vec4 wT = texture(w, coords + vec2(0, 1));
	
	div = rdx * ((wR.x - wL.x) + (wT.y - wB.y));
}

void gradient(vec2 coords,
	float rdx,
	sampler2DRect p,
	sampler2DRect w,
	out vec4 uNew)
{
	float pL = texture(p, coords - vec2(1, 0)).x;
	float pR = texture(p, coords + vec2(1, 0)).x;
	float pB = texture(p, coords - vec2(0, 1)).x;
	float pT = texture(p, coords + vec2(0, 1)).x;

	uNew = texture(w, coords);
	uNew.xy -= rdx * vec2(pR - pL, pT - pB);
}

void main()
{

}