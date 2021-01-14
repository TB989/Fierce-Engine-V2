#version 430 core

in vec3 position;
in vec3 color;

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;

out vec3 color_vs;

void main() {
	gl_Position=projectionMatrix*modelMatrix*vec4(position,1.0);
	color_vs=color;
}