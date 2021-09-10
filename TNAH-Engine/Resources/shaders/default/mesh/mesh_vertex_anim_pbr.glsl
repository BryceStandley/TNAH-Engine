#version 430 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec3 a_Tangent;
layout(location = 3) in vec3 a_Binormal;
layout(location = 4) in vec2 a_TexCoord;

layout(location = 5) in ivec4 a_BoneIndices;
layout(location = 6) in vec4 a_BoneWeights;

uniform Camera
{
    mat4 u_ViewMatrix;
	mat4 u_ViewProjectionMatrix;
};

uniform mat4 u_LightMatrixCascade0;
uniform mat4 u_LightMatrixCascade1;
uniform mat4 u_LightMatrixCascade2;
uniform mat4 u_LightMatrixCascade3;

const int MAX_BONES = 100;
uniform Transform
{
	mat4 u_Transform;
	mat4 u_BoneTransforms[100];
};

struct VertexOutput
{
	vec3 WorldPosition;
    vec3 Normal;
	vec2 TexCoord;
	mat3 WorldNormals;
	mat3 WorldTransform;
	vec3 Binormal;
	
	vec3 ViewPosition;
};

layout (location = 0) out VertexOutput Output;

void main()
{
	mat4 boneTransform = u_BoneTransforms[a_BoneIndices[0]] * a_BoneWeights[0];
    boneTransform += u_BoneTransforms[a_BoneIndices[1]] * a_BoneWeights[1];
    boneTransform += u_BoneTransforms[a_BoneIndices[2]] * a_BoneWeights[2];
    boneTransform += u_BoneTransforms[a_BoneIndices[3]] * a_BoneWeights[3];

	vec4 localPosition = boneTransform * vec4(a_Position, 1.0);

	Output.WorldPosition = vec3(u_Transform * boneTransform * vec4(a_Position, 1.0));
    Output.Normal = mat3(u_Transform) * mat3(boneTransform) * a_Normal;
	Output.TexCoord = vec2(a_TexCoord.x, 1.0 - a_TexCoord.y);
	Output.WorldNormals = mat3(u_Transform) * mat3(a_Tangent, a_Binormal, a_Normal);
	Output.Binormal = mat3(boneTransform) * a_Binormal;
	Output.ViewPosition = vec3(u_ViewMatrix * vec4(Output.WorldPosition, 1.0));

	gl_Position = u_ViewProjectionMatrix * u_Transform * localPosition;
}