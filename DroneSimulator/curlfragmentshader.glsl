#version 330 core

precision mediump float;
precision mediump sampler2D;

varying highp vec3 vUv;
varying highp vec3 vL;
varying highp vec3 vR;
varying highp vec3 vF;
varying highp vec3 vB;
varying highp vec3 vU;
varying highp vec3 vD;
uniform sampler3D uVelocity;

out vec4 FragColor;

void main () {
    float L = texture3D(uVelocity, vL).y;
    float R = texture3D(uVelocity, vR).y;
    float T = texture3D(uVelocity, vF).x;
    float B = texture3D(uVelocity, vB).x;
    float vorticity = R - L - T + B;
    
    FragColor = vec4(0.5 * vorticity, 0.0, 0.0, 1.0);
}