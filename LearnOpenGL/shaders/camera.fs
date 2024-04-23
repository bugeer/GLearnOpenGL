#version 330 core

in vec2 vUv;
out vec4 FragColor;

uniform sampler2D t2d01;
uniform sampler2D t2d02;

void main() {
    FragColor = mix(texture(t2d01, vUv), texture(t2d02, vUv), 0.2);
}
