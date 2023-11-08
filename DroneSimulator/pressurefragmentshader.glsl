#version 330 core

precision mediump float;
precision mediump sampler3D;

varying highp vec3 vUv;
varying highp vec3 vL;
varying highp vec3 vR;
varying highp vec3 vF;
varying highp vec3 vB;
varying highp vec3 vU;
varying highp vec3 vD;

uniform sampler3D uPressure;
uniform sampler3D uDivergence;

out vec4 FragColor;

void main () {
    float L = texture3D(uPressure, vL).x;
    float R = texture3D(uPressure, vR).x;
    float F = texture3D(uPressure, vF).x;
    float B = texture3D(uPressure, vB).x;
    float U = texture3D(uPressure, vU).x;
    float D = texture3D(uPressure, vD).x;
    float C = texture3D(uPressure, vUv).x;
    float divergence = texture3D(uDivergence, vUv).x;
    float pressure = (L + R + B + F + D + U - divergence) / 6;
    FragColor = vec4(pressure, 0.0, 0.0, 1.0);
}