#version 330 core
out vec4 FragColor;
uniform vec3 color;
varying vec2 val;
void main()
{
	float R = 1.0; 
	float R2 = 0.9;
	float dist = sqrt(dot(val, val));
	if (dist >= R || dist <= R2)
	{
		discard;
	}
	FragColor = vec4(color, 1.0f);
}