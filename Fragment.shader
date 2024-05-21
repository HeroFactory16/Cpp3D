#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

struct Material {
	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;
	float shininess;
	};

struct Light {
	vec3 lightPositon;

	vec3 ambientIntensity;
	vec3 diffuseIntensity;
	vec3 specularIntensity;
	};

uniform Material material;
uniform Light light;
uniform sampler2D texture1;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	vec3 ambient = material.ambientColor * light.ambientIntensity;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * material.diffuseColor) * light.diffuseIntensity;

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = material.specularColor * spec * light.specularIntensity;

	ivec2 texSize = textureSize(texture1, 0);
	if (texSize.x != 1 && texSize.y != 1) {
		vec4 textureColor = texture(texture1, TexCoord);
		FragColor = vec4(textureColor.rgb * (ambient + diffuse + specular), 1.0f);
		}
	else {
		FragColor = vec4((ambient + diffuse + specular), 1.0f);
		}
};