#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec3 a_Tangent;
layout(location = 3) in vec3 a_Binormal;
layout(location = 4) in vec2 a_TexCoord;

layout(std140, binding = 0) uniform u_Camera
{
	mat4 u_ViewProjectionMatrix;
	mat4 u_InverseViewProjectionMatrix;
	mat4 u_ProjectionMatrix;
	mat4 u_ViewMatrix;
};

layout(std140, binding = 1) uniform ShadowData
{
	mat4 u_LightMatrix[4];
};

layout(push_constant) uniform Transform
{
	mat4 Transform;
} u_Renderer;

struct VertexOutput
{
	vec3 WorldPosition;
	vec3 Normal;
	vec2 TexCoord;
	mat3 WorldNormals;
	mat3 WorldTransform;
	vec3 Binormal;

	mat3 CameraView;

	vec4 ShadowMapCoords[4];
	vec3 ViewPosition;
};

layout(location = 0) out VertexOutput Output;

void main()
{
	Output.WorldPosition = vec3(u_Renderer.Transform * vec4(a_Position, 1.0));
	Output.Normal = mat3(u_Renderer.Transform) * a_Normal;
	Output.TexCoord = vec2(a_TexCoord.x, 1.0 - a_TexCoord.y);
	Output.WorldNormals = mat3(u_Renderer.Transform) * mat3(a_Tangent, a_Binormal, a_Normal);
	Output.WorldTransform = mat3(u_Renderer.Transform);
	Output.Binormal = a_Binormal;

	Output.CameraView = mat3(u_ViewMatrix);

	Output.ShadowMapCoords[0] = u_LightMatrix[0] * vec4(Output.WorldPosition, 1.0);
	Output.ShadowMapCoords[1] = u_LightMatrix[1] * vec4(Output.WorldPosition, 1.0);
	Output.ShadowMapCoords[2] = u_LightMatrix[2] * vec4(Output.WorldPosition, 1.0);
	Output.ShadowMapCoords[3] = u_LightMatrix[3] * vec4(Output.WorldPosition, 1.0);
	Output.ViewPosition = vec3(u_ViewMatrix * vec4(Output.WorldPosition, 1.0));

	gl_Position = u_ViewProjectionMatrix * u_Renderer.Transform * vec4(a_Position, 1.0);
}