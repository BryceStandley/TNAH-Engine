//Mesh Vertex
#version 330 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec3 a_Tangent;
layout(location = 3) in vec3 a_Binormal;
layout(location = 4) in vec2 a_TexCoord;

layout(location = 5) in vec4 a_BoneIDs;
layout(location = 6) in vec4 a_BoneWeights;

out vec3 v_Position;
out vec2 v_TexCoord;
out vec3 v_Normal;
out vec4 v_WorldPosition;

const int MAX_BONES = 100;

uniform mat4 u_ViewProjectionMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_CameraPosition;
uniform mat4 u_Transform;
uniform mat4 u_BoneTransform[MAX_BONES];



void main()
{
    v_WorldPosition = u_Transform * vec4(a_Position, 1.0f);
    vec4 positionRelToCamea = u_ViewMatrix * v_WorldPosition;
    float distance = length(positionRelToCamea.xyz);
    v_Normal = mat3(transpose(inverse(u_Transform))) * a_Normal;


	mat4 boneTransform   = u_BoneTransform[int(a_BoneIDs[0])] * a_BoneWeights[0];
    boneTransform       += u_BoneTransform[int(a_BoneIDs[1])] * a_BoneWeights[1];
    boneTransform       += u_BoneTransform[int(a_BoneIDs[2])] * a_BoneWeights[2];
    boneTransform       += u_BoneTransform[int(a_BoneIDs[3])] * a_BoneWeights[3];

	vec4 pos = boneTransform * vec4(a_Position, 1.0f);
	
	v_Position = vec3(u_Transform * vec4(a_Position, 1.0));
	v_TexCoord = a_TexCoord;
	
	gl_Position = u_ViewProjectionMatrix * u_Transform * pos;
	/*
    gl_Position = u_ViewProjectionMatrix * localPosition;
	v_TexCoord = a_TexCoord;
	vec4 Normal = boneTransform * vec4(a_Normal, 1.0f);
	v_Normal = (u_ViewMatrix * Normal).xyz;
	v_WorldPosition = (u_ViewMatrix * localPosition).xyz;
	*/

	
}
