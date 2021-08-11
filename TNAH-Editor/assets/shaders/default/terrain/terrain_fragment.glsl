#version 330 core
out vec4 color;

struct Material
{
	float shininess;
	float metalness;
};

struct Light {
	int type;
	vec3 cameraPosition;
	vec3 position;
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 color;
	
	float constant;
	float linear;
	float quadratic;
	
	float cutoff;
	
};

in vec3 v_Position;
in float v_Height;
in vec3 v_Normal;
in vec2 v_TextureCoord;

uniform Light u_Light;
uniform Material u_Material;

uniform sampler2D u_dirtTexture;
uniform sampler2D u_grassTexture;
uniform sampler2D u_rockTexture;
uniform sampler2D u_snowTexture;
uniform sampler2D u_detailTexture;

float scaleFactor = 1.0f;

int dirtStart = 0;
int grassStart = 60;
int rockStart = 100;
int snowStart = 200;

vec4 CalculateDirectionalLighting()
{
	vec3 ambient = u_Light.ambient * color.rgb;
	// diffuse 
	vec3 norm = normalize(v_Normal);

	vec3 lightDir = normalize(-u_Light.direction);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = u_Light.diffuse * diff * color.rgb;
	// specular
	vec3 viewDir = normalize(u_Light.cameraPosition - v_Position);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
	vec3 specular = u_Light.specular * spec * color.rgb;

	vec4 result = vec4(ambient + diffuse + specular, 1.0f);
	return result;
}

vec4 CalculatePointLighting()
{
	vec4 result;

	return result;

}

vec4 CalculateSpotLighting()
{
	vec4 result;

	return result;
}

void main()
{
	vec2 texCoords = (v_TextureCoord - 0.5) * scaleFactor + (0.5f * scaleFactor);
	
	vec4 dirt = texture(u_dirtTexture, texCoords);
	vec4 grass = texture(u_grassTexture, texCoords);
	vec4 rock = texture(u_rockTexture, texCoords);
	vec4 snow = texture(u_snowTexture, texCoords);
	vec4 detail = texture(u_detailTexture, texCoords);
	
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
	
	
	if(u_Light.type == 0)
	{
		//directional light
		color = (color * detail) * CalculateDirectionalLighting();
	}
	else if(u_Light.type == 1)
	{
		//point light
		color = (color * detail) * CalculatePointLighting();
	}
	else if(u_Light.type == 2)
	{
		//Spot Light
		color = (color * detail) * CalculateSpotLighting();
	}
	else
	{
		// No light, default fully lit
		color = (color * detail) * vec4(1.0f);
	}
}

