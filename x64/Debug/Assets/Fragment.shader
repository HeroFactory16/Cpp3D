#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture1;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform float ambientStrength;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	// FragColor = vec4(0.33f, 0.66f, 0.99f, 1.0f);
	//FragColor = texture(texture1, TexCoord);

	float specularStrength = 0.5f;

	vec3 ambient = ambientStrength * lightColor;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 150);
	vec3 specular = specularStrength * spec * lightColor;

	ivec2 texSize = textureSize(texture1, 0);
	if (texSize.x != 1 && texSize.y != 1) {
		vec4 textureColor = texture(texture1, TexCoord);
		FragColor = vec4(objectColor * textureColor.rgb * (ambient + diffuse + specular), 1.0f);
		}
	else {
		FragColor = vec4(objectColor * (ambient + diffuse + specular), 1.0f);
		}
};