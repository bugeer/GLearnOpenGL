#version 330 core

in vec2 aUv;
in vec3 aColor;
out vec4 FragColor;

uniform sampler2D t2d;

void main() {
    FragColor = texture(t2d, aUv) * vec4(aColor, 1.0);
}