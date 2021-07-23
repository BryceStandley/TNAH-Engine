#type vertex
#version 330 core
layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Color;
layout (location = 2) in vec3 a_TextureCoord;
layout (location = 3) in vec3 a_Normal;

out vec3 v_Color;
//out vec2 texCoord;
//out vec3 Normal;
//out vec3 v_Position;
//out float height;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;


void main()
{
	//v_Position = a_Position;
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0f);
	vec3 Normal = mat3(transpose(inverse(u_Transform))) * a_Normal;

	//texCoord = vec2(a_TextureCoord.x, a_TextureCoord.z);
	//height = a_Color.y * 255;
	v_Color = a_Color;
	
}

#type fragment
#version 330 core
layout(location = 0) out vec4 color;

in vec3 v_Color;
//in vec2 texCoord;
//in float height;
//in vec3 Normal;
//in vec3 v_Position;

//uniform vec3 lightPos;
//uniform vec3 u_Transform;
//uniform vec3 lightColor;

//uniform sampler2D texture0; //dirt
//uniform sampler2D texture1; //grass
//uniform sampler2D texture2; //mountain
//uniform sampler2D texture3; //snow
//uniform sampler2D texture4; //detail

//vec4 dirt = texture(texture1, texCoord);
//vec4 grass = texture(texture0, texCoord);
//vec4 mountain = texture(texture2, texCoord);
//vec4 snow = texture(texture3, texCoord);
//vec4 detail = texture(texture4, texCoord);

//int dirtStart = 0;
//int grassStart = 40;
//int mountainStart = 80;
//int snowStart = 250;

void main()
{
	/*
	if(height > snowStart)
	{
		FragColor = snow;
	}
	else if (height > mountainStart)
	{
		float blend = (height - mountainStart) / (snowStart - mountainStart);
		FragColor = mix(mountain, snow, blend);
	}
	else if (height > grassStart)
	{
		float blend = (height - grassStart) / (mountainStart - grassStart);
		FragColor = mix(grass, mountain, blend);
	}
	else if (height > dirtStart)
	{
		float blend = (height - dirtStart) / (grassStart - dirtStart);
		FragColor = mix(dirt, grass, blend);
	}
	else
	{
		FragColor = dirt;
	}

	// ambient
	float ambientStrength = 0.4;
	vec3 ambient = ambientStrength * lightColor;
	
	// diffuse 
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
	
	// specular
	float specularStrength = 0.05;
	vec3 viewDir = normalize(u_Transform - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);  
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;  
		
	vec3 result = (ambient + diffuse + specular);

	FragColor = (FragColor * detail) * vec4(result, 1.0f);
	*/
	color = vec4(v_Color,1.0f);//vec4(1.0f, 1.0f, 1.0f, 1.0f);
}