#version 330 core

//precision highp float;

layout (location = 0) in vec3 aPosition;

varying vec3 vUv;
varying vec3 vL;
varying vec3 vR;
varying vec3 vF;
varying vec3 vB;
varying vec3 vU;
varying vec3 vD;

uniform vec3 texelSize;

void main () {
    vUv = aPosition * 0.5 + 0.5;
    vL = vUv - vec3(texelSize.x, 0.0, 0.0);
    vR = vUv + vec3(texelSize.x, 0.0, 0.0);
    vU = vUv + vec3(0.0, texelSize.y, 0.0);
    vD = vUv - vec3(0.0, texelSize.y, 0.0);
    vF = vUv + vec3(0.0, 0.0, texelSize.z);
    vB = vUv - vec3(0.0, 0.0, texelSize.z);

    gl_Position = vec4(aPosition.x, aPosition.y, aPosition.z, 1.0);
}