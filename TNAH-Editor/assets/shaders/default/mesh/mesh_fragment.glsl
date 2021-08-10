#version 330 core
out vec4 color;

in vec2 v_TexCoord;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

void main()
{
	//color = texture(texture_diffuse1, v_TexCoord);
	//color = texture(texture_specular1, v_TexCoord);
	color = vec4(1.0f);
	if(color.a < 0.1)
	{
		discard;
	}
}