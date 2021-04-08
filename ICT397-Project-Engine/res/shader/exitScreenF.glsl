#version 330
out vec4 FragColour;
in vec2 TexCoord;

uniform sampler2D texture;

void main()
{
    FragColour = texture(texture, TexCoord);
}
