precision mediump float;
precision mediump sampler3D;

varying highp vec3 vUv;
uniform sampler3D uTexture;
uniform float value;

out vec4 FragColor;

void main () {
    FragColor = value * texture3D(uTexture, vUv);
}