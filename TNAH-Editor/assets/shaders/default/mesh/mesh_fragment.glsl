#version 330 core
out vec4 color;

struct Material
{
	float shininess;
	float metalness;
	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
	bool diffuse_bound;
	bool specular_bound;
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
	float intensity;

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
	vec3 specular;
	if(!u_Material.specular_bound)
	{
		specular = u_Light.specular * spec * texture(u_Material.texture_specular1, v_TexCoord).rgb;
	}
	else
	{
		specular = u_Light.specular * spec * texture(u_Material.texture_diffuse1, v_TexCoord).rgb;
	}
	
	vec3 result = vec3(ambient + diffuse + specular);
	result = (result * u_Light.intensity) * u_Light.color;
	return vec4(result, 1.0f);
}

vec4 CalculatePointLighting()
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
	vec3 specular;
	if(!u_Material.specular_bound)
	{
		specular = u_Light.specular * spec * texture(u_Material.texture_specular1, v_TexCoord).rgb;
	}
	else
	{
		specular = u_Light.specular * spec * texture(u_Material.texture_diffuse1, v_TexCoord).rgb;
	}

	// attenuation
	float distance    = length(u_Light.position - v_Position);
	float attenuation = 1.0 / (u_Light.constant + u_Light.linear * distance + u_Light.quadratic * (distance * distance));

	ambient  *= attenuation;
	diffuse   *= attenuation;
	specular *= attenuation;

	vec3 result = vec3(ambient + diffuse + specular);
	result = (result * u_Light.intensity) * u_Light.color;
	return vec4(result, 1.0f);
}

vec4 CalculateSpotLighting()
{
	vec3 lightDir = normalize(u_Light.position - v_Position);
	// check if lighting is inside the spotlight cone
	float theta = dot(lightDir, normalize(-u_Light.direction));

	if(theta > u_Light.cutoff) // remember that we're working with angles as cosines instead of degrees so a '>' is used.
	{
		// ambient
		vec3 ambient = u_Light.ambient * texture(u_Material.texture_diffuse1, v_TexCoord).rgb;

		// diffuse 
		vec3 norm = normalize(v_Normal);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = u_Light.diffuse * diff * texture(u_Material.texture_diffuse1, v_TexCoord).rgb;

		// specular
		vec3 viewDir = normalize(u_Light.cameraPosition - v_Position);
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(u_Light.cameraPosition, reflectDir), 0.0), u_Material.shininess);
		
		vec3 specular;
		if(!u_Material.specular_bound)
		{
			specular = u_Light.specular * spec * texture(u_Material.texture_specular1, v_TexCoord).rgb;
		}
		else
		{
			specular = u_Light.specular * spec * texture(u_Material.texture_diffuse1, v_TexCoord).rgb;
		}

		// attenuation
		float distance    = length(u_Light.position - v_Position);
		float attenuation = 1.0 / (u_Light.constant + u_Light.linear * distance + u_Light.quadratic * (distance * distance));

		// ambient  *= attenuation; // remove attenuation from ambient, as otherwise at large distances the light would be darker inside than outside the spotlight due the ambient term in the else branche
		diffuse   *= attenuation;
		specular *= attenuation;

		vec3 result = vec3(ambient + diffuse + specular);
		result = (result * u_Light.intensity) * u_Light.color;
		return vec4(result, 1.0f);
	}
	else
	{
		// else, use ambient light so scene isn't completely dark outside the spotlight.
		vec3 result = vec3(u_Light.ambient * color.rgb);
		result = (result * u_Light.intensity) * u_Light.color;
		return vec4(result, 1.0f);
	}
}

void main()
{
	
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
		color = texture(u_Material.texture_diffuse1, v_TexCoord);
	}
	
	//if the alpha channel is less than 0.1, discard the pixel as it should be transparent
	if(color.a < 0.1f)
	{
		discard;
	}
}