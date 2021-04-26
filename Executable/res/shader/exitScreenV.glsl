#version 330
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aTexCoord;

out TexCoord;
out colour;
void main()
{
    gl_Position = vec4(aPos, 1.0);
    colour = vec3(1,1,1);
    TexCoord = aTexCoord;
}
