#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 value;
uniform mat4 MVP;
varying vec2 val;
void main()
{
   gl_Position = MVP * vec4(pos.x, pos.y, pos.z, 1.0);
   val = value;
}