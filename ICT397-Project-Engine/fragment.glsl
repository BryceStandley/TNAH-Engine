#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in float height;
in vec3 Normals;
in vec3 FragPos; 

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;


uniform sampler2D texture0; //dirt
uniform sampler2D texture1; //grass
uniform sampler2D texture2; //mountain
uniform sampler2D texture3; //snow
uniform sampler2D texture4; //detail

vec4 tex0 = texture(texture0, texCoord);
vec4 tex1 = texture(texture1, texCoord);
vec4 tex2 = texture(texture2, texCoord);
vec4 tex3 = texture(texture3, texCoord);
vec4 detail = texture(texture4, texCoord);

int tex0Start = 40;
int tex1Start = 75;
int tex2Start = 150;
int tex3Start = 200;

void main()
{	
	if(height > tex3Start)
	{
		FragColor = tex3;
	}
	else if (height > tex2Start)
	{
		float blend = (height - tex2Start) / (tex3Start - tex2Start);
		FragColor = mix(tex2, tex3, blend);
	}
	else if (height > tex1Start)
	{
		float blend = (height - tex1Start) / (tex2Start - tex1Start);
		FragColor = mix(tex1, tex2, blend);
	}
	else if (height > tex0Start)
	{
		float blend = (height - tex0Start) / (tex1Start - tex0Start);
		FragColor = mix(tex0, tex1, blend);
	}
	else
	{
		FragColor = tex0;
	}
	
	// ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(Normals);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // specular
    float specularStrength = 0.05;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  
        
    vec3 result = (ambient + diffuse + specular);
    
	FragColor = (FragColor * detail); //* vec4(result, 1.0);

}