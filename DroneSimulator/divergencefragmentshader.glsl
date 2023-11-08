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
uniform sampler3D uVelocity;

out vec4 FragColor;

void main () {
    float L = texture3D(uVelocity, vL).x;
    float R = texture3D(uVelocity, vR).x;
    float F = texture3D(uVelocity, vF).z;
    float B = texture3D(uVelocity, vB).z;
    float U = texture3D(uVelocity, vU).y;
    float D = texture3D(uVelocity, vD).y;

    vec3 C = texture3D(uVelocity, vUv).xyz;
    if (vL.x < 0.0) { L = -C.x; }
    if (vR.x > 1.0) { R = -C.x; }
    if (vF.z > 1.0) { F = -C.z; }
    if (vB.z < 0.0) { B = -C.z; }
    if (vU.y > 1.0) { U = -C.y; }
    if (vU.y < 0.0) { D = -C.y; }

    float div = 0.5 * (R - L + U - D);
    FragColor = vec4(div, 0.0, 0.0, 1.0);
}