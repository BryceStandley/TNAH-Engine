//TNAH Physics Collider Shader
//Basic shader for drawing ReactPhysics3D colliders within the application.

#type vertex

#version 330 core

uniform mat4 u_ViewProjectionMatrix;
uniform mat4 u_Transform;

layout (location = 0) in vec3 a_Position;
layout (location = 1) in uint a_VertexColor;

out vec4 v_VertexColor;

void main() 
{
    gl_Position = u_ViewProjectionMatrix * u_Transform * vec4(a_Position, 1.0f);
    
    v_VertexColor = vec4((a_VertexColor & 0xFF0000u) >> 16, (a_VertexColor & 0x00FF00u) >> 8, a_VertexColor & 0x0000FFu, 0xFF);
}

#type fragment

#version 330 core

uniform bool u_isGlobalVertexColorEnabled;
uniform vec4 u_GlobalVertexColor;

in vec4 v_VertexColor;

out vec4 color;

void main()
 {
    if (u_isGlobalVertexColorEnabled) 
    {
        color = u_GlobalVertexColor;
    }
    else 
    {
        color = v_VertexColor;
    }
}