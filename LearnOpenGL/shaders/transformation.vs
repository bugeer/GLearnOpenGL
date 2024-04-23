#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUv;

out vec2 vUv;

uniform mat4 transform;

void main() {
	vUv = aUv;
	gl_Position = transform * vec4(aPos, 1.0);
}
