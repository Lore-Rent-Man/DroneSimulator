precision mediump float;
precision mediump sampler3D;

varying highp vec3 vUv;
uniform sampler3D uTexture;
uniform float value;

void main () {
    gl_FragColor = value * texture3D(uTexture, vUv);
}