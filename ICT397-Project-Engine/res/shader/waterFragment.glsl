#version 330 core

//in vec2 textureCoords;
in vec4 vertexColour;
in vec3 FragPos;

out vec4 out_Color;


void main(void)
{

    //out_Color = vec4(0.0, 0.0, 1.0, 1.0);
    out_Color = vertexColour;
}