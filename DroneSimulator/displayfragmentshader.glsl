#version 330 core

precision highp float;
precision highp sampler3D;

in vec3 vUv;

uniform sampler3D uVelocity;

out vec4 FragColor;

void main () {
    vec3 x = texture3D(uVelocity, vUv).rgb;
    float a = max(x.r, max(x.g, x.b));
    FragColor = vec4(x, a);
}