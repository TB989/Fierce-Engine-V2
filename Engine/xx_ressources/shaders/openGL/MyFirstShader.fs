#version 430 core

in vec3 color_vs;

layout(location = 0) out vec4 outColor;

void main() {
    outColor = vec4(color_vs, 1.0);
}