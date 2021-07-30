#version 330 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec4 a_Texture;
layout(location = 3) in vec4 a_Normal;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec3 v_Position;
out vec4 v_Color;

void main()
{
	v_Position = a_Position;
	v_Color = a_Color;
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position.x, a_Position.y, a_Position.z, 1.0);	
}