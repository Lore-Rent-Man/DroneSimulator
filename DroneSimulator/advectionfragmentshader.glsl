#version 330 core

precision highp float;
precision highp sampler3D;

in vec3 vUv;
uniform sampler3D uVelocity;
uniform sampler3D uSource;
uniform vec3 texelSize;
uniform float dt;
uniform float dissipation;

out vec4 FragColor;

void main () {
    vec3 coord = vUv - dt * texture3D(uVelocity, vUv).xyz * texelSize;
    vec4 result = texture3D(uSource, coord);
    float decay = 1.0 + dissipation * dt;
    FragColor = result/decay;
}