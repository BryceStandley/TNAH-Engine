#version 330 core
layout (location = 0) in vec3 aPos;

//out vec2 TexCoords;
out vec4 vertexColour;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0f));
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    vertexColour = vec4(0.0, 0.0, 1.0, 1.0);
}