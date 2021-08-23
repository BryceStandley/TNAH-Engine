#version 330 core
layout (location = 0) in vec3 a_Position;

out vec3 v_TexCoords;

uniform mat4 u_ViewProjection;

void main()
{
    vec4 pos = u_ViewProjection* vec4(a_Position, 1.0f);
	gl_Position = pos.xyww;
	v_TexCoords = a_Position;
	
}