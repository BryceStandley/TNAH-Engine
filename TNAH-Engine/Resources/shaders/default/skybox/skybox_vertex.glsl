#version 330 core
layout (location = 0) in vec3 a_Position;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    vec4 pos = projection * view * vec4(position, 1.0f);
	gl_Position = pos.xyww;
	TexCoords = position;
	
}