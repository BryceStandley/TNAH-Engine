#version 330 core
out vec4 FragColor;

in vec3 v_TexCoords;

uniform samplerCube u_SkyboxTexture;

void main()
{
	FragColor = texture(u_SkyboxTexture, v_TexCoords);
}

	
	
	
	
