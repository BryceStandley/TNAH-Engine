#version 330 core
			
layout(location = 0) out vec4 color;

in vec3 v_Position;
in vec4 v_Color;
in float v_Height;
in vec3 v_Normal;
in vec2 v_TextureCoord;

uniform vec3 u_LightPosition;
uniform vec3 u_CameraPosition;
uniform vec3 u_LightColor;

uniform sampler2D u_DirtTexture;
uniform sampler2D u_GrassTexture;
uniform sampler2D u_RockTexture;
uniform sampler2D u_SnowTexture;
uniform sampler2D u_DetailTexture;

vec4 dirt = texture(u_DirtTexture, v_TextureCoord);
vec4 grass = texture(u_GrassTexture, v_TextureCoord);
vec4 rock = texture(u_RockTexture, v_TextureCoord);
vec4 snow = texture(u_SnowTexture, v_TextureCoord);
vec4 detail = texture(u_DetailTexture, v_TextureCoord);

int dirtStart = 0;
int grassStart = 40;
int rockStart = 80;
int snowStart = 250;

void main()
{
	if(v_Height > snowStart)
	{
		color = snow;
	}
	else if(v_Height > rockStart)
	{
		float blend = (v_Height - rockStart) / (snowStart - rockStart);
		color = mix(rock, snow, blend);
	}
	else if(v_Height > grassStart)
	{
		float blend = (v_Height - grassStart) / (rockStart - grassStart);
		color = mix(grass, snow, blend);
	}
	else if(v_Height > dirtStart)
	{
		float blend = (v_Height - dirtStart) / (grassStart - dirtStart);
		color = mix(dirt, grass, blend);
	}
	else
	{
		color = dirt;
	}
	
	//Lighting
	float ambientStrength = 0.4f;
	vec3 ambient = ambientStrength * u_LightColor;
	
	vec3 norm = normalize(v_Normal);
	vec3 lightDirection = normalize(u_LightPosition - v_Position);
	float difference = max(dot(norm, lightDirection), 0.0f);
	vec3 diffuse = difference * u_LightColor;
	
	float specularStrength = 0.05f;
	vec3 cameraDirection = normalize(u_CameraPosition - v_Position);
	vec3 reflecDirection = reflect(-lightDirection, norm);
	float spec = pow(max(dot(cameraDirection, reflecDirection), 0.0f), 32);
	vec3 specular = specularStrength * spec * u_LightColor;
	
	vec3 result = (ambient + diffuse + specular);
	color = (color * detail) * vec4(result, 1.0f);

}