#version 330 core
layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec3 a_Tangent;
layout (location = 3) in vec3 a_Bitangent;
layout (location = 4) in vec2 a_TexCoord;

out vec3 v_Position;
out vec2 v_TexCoord;
out vec3 v_Normal;


uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

void main()
{
	v_TexCoord = a_TexCoord;
	v_Normal = a_Normal;
	v_Position = a_Position;
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
}
