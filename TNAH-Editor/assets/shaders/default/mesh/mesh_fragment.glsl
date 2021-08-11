#version 330 core
out vec4 color;

struct Material
{
	float shininess;
	float metalness;
	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
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
in vec2 v_TexCoord;
in vec3 v_Normal;

uniform Light u_Light;
uniform Material u_Material;


vec4 CalculateDirectionalLighting()
{
	vec3 ambient = u_Light.ambient * texture(u_Material.texture_diffuse1, v_TexCoord).rgb;
	// diffuse 
	vec3 norm = normalize(v_Normal);

	vec3 lightDir = normalize(-u_Light.direction);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = u_Light.diffuse * diff * texture(u_Material.texture_diffuse1, v_TexCoord).rgb;
	// specular
	vec3 viewDir = normalize(u_Light.cameraPosition - v_Position);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
	vec3 specular = u_Light.specular * spec * texture(u_Material.texture_specular1, v_TexCoord).rgb;

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
	color = texture(u_Material.texture_diffuse1, v_TexCoord) * texture(u_Material.texture_specular1, v_TexCoord);
	
	if(u_Light.type == 0)
	{
		//directional light
		color = CalculateDirectionalLighting();
	}
	else if(u_Light.type == 1)
	{
		//point light
		color =  CalculatePointLighting();
	}
	else if(u_Light.type == 2)
	{
		//Spot Light
		color = CalculateSpotLighting();
	}
	else
	{
		// No light, default fully lit
		color = color;
	}
	
	//if the alpha channel is less than 0.1, discard the pixel as it should be transparent
	if(color.a < 0.1f)
	{
		discard;
	}
}