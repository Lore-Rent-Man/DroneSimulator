#version 330 core

precision highp float;
precision highp sampler3D;

in vec3 vUv;

uniform sampler3D uVelocity;

out vec4 FragColor;

void main () {
	FragColor = texture3D(uVelocity, vUv);
}