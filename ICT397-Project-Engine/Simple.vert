// Simple.vert
#version 330

in vec3 position;

void main(void) {
    gl_Position = vec4(position, 1.0);
}