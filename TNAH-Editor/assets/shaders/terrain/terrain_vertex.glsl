#version 330 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec4 a_Texture;
layout(location = 3) in vec4 a_Normal;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec3 v_Position;
out vec4 v_Color;
out float v_Height;
out vec3 v_Normal;
out vec2 v_TextureCoord;

void main()
{
	v_Position = a_Position;
	v_Color = a_Color;
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
	v_Normal = mat3(transpose(inverse(u_Transform))) * vec3(a_Normal.xyz);
	v_Height = a_Color.y * 255;
}