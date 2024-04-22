#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aUv;

out vec2 vUv;
out vec3 oColor;

void main() {
	gl_Position = vec4(aPos, 1.0);
	vUv = aUv;
	oColor = aColor;
}