#version 330 core
			
out vec4 color;

in vec3 v_Position;
in float v_Height;
in vec3 v_Normal;
in vec2 v_TextureCoord;

uniform vec3 u_LightPosition;
uniform vec3 u_CameraPosition;
uniform vec3 u_LightColor;

uniform sampler2D u_dirtTexture;
uniform sampler2D u_grassTexture;
uniform sampler2D u_rockTexture;
uniform sampler2D u_snowTexture;
uniform sampler2D u_detailTexture;

vec4 dirt = texture(u_dirtTexture, v_TextureCoord);
vec4 grass = texture(u_grassTexture, v_TextureCoord);
vec4 rock = texture(u_rockTexture, v_TextureCoord);
vec4 snow = texture(u_snowTexture, v_TextureCoord);
vec4 detail = texture(u_detailTexture, v_TextureCoord);

int dirtStart = 0;
int grassStart = 60;
int rockStart = 100;
int snowStart = 200;

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