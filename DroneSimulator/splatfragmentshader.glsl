#version 330 core

precision highp float;
precision highp sampler3D;

varying vec3 vUv;
uniform sampler3D uTarget;
uniform float aspectRatio;
uniform vec3 color;
uniform vec3 point;
uniform float radius;

out vec4 FragColor;

void main () {
    vec3 p = vUv.xyz - point.xyz;
    p.x *= aspectRatio; 
    vec3 splat = exp(-dot(p, p) / radius) * color;
    vec3 base = texture3D(uTarget, vUv).xyz;
    FragColor = vec4(base + splat, 1.0);
}