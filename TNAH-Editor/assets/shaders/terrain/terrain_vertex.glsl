#version 330 core
layout (location = 0) in vec3 a_Position;
//layout (location = 1) in vec3 a_Color;
//layout (location = 2) in vec3 a_TextureCoord;
//layout (location = 3) in vec3 a_Normal;

//out vec3 v_Color;
//out vec2 texCoord;
//out vec3 Normal;
out vec3 v_Position;
//out float height;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;
uniform mat4 u_Model;


void main()
{
	v_Position = a_Position;
	gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0f);
	//vec3 Normal = mat3(transpose(inverse(u_Transform))) * a_Normal;

	//texCoord = vec2(a_TextureCoord.x, a_TextureCoord.z);
	//height = a_Color.y * 255;
	//v_Color = a_Color;
	
}