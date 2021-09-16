//TNAH Skybox Shader
//PBR Support - IN Development

#type vertex

#version 330 core
layout (location = 0) in vec3 a_Position;

out vec3 v_TexCoords;

uniform mat4 u_View;
uniform mat4 u_ViewProjection;
uniform vec3 u_CameraPosition;

void main()
{
	v_TexCoords = a_Position;
	gl_Position = u_ViewProjection * vec4(a_Position + u_CameraPosition, 1.0f);	
}

#type fragment

#version 330 core
out vec4 FragColor;

in vec3 v_TexCoords;

uniform samplerCube u_SkyboxTexture;

void main()
{
	vec4 tex = texture(u_SkyboxTexture, v_TexCoords);
	FragColor = tex;
}