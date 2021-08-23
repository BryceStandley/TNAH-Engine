#version 330 core
layout (location = 0) in vec3 a_Position;

out vec3 v_TexCoords;

uniform mat4 u_View;
uniform mat4 u_Projection;
uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

void main()
{
	v_TexCoords = a_Position;
	
	vec4 pos = u_Projection * u_View * u_Transform * vec4(a_Position, 1.0f);
	//vec4 pos = u_ViewProjection * vec4(a_Position, 1.0f);
	gl_Position = pos.xyww;
	
	
}