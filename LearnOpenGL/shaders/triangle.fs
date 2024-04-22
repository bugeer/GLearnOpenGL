#version 330 core

in vec3 oColor;
in vec3 oPos;
out vec4 finalColor;

void main() {
    finalColor = vec4(oColor, 1.0);
    // finalColor = vec4(oPos, 1.0);
}