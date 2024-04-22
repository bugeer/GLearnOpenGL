#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 oColor;
out vec3 oPos;

uniform float dir = 1.0;
uniform vec2 offset = vec2(0.0, 0.0);

void main() {
	gl_Position = vec4(aPos.x + offset.x, aPos.y * dir + offset.y, aPos.z, 1.0);
	oPos = aPos;
	oColor = aColor;
}