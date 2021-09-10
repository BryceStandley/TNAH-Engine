//Mesh Fragment
#version 330 core

out vec4 FragColor;

in vec3 v_Position;
in vec2 v_TexCoord;
in vec3 v_Normal;
in vec4 v_WorldPosition;


uniform sampler2D u_Diffuse0;

void main()
{
    FragColor = texture(u_Diffuse0, v_TexCoord);
}