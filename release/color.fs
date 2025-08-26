#version 330 core

in vec3 fragPos;
in vec3 normal;

out vec4 fragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

uniform vec3 viewPos;

void main()
{
  float ambientStrength = 0.1;
  vec3 ambient = ambientStrength * lightColor; //ambient light

  vec3 norm = normalize(normal); //normalizing normal vector to be between 1 - 0
  vec3 lightDir = normalize(lightPos - fragPos); //finding direction vector of light source

  vec3 viewDir = normalize(viewPos - fragPos);
  vec3 reflectDir = reflect(-lightDir, norm);

  float specularStrength = 0.5;
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32); // 32 is the shinines of the highlight
  vec3 specular = specularStrength * spec * lightColor;

  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * lightColor;

  vec3 result = (ambient + diffuse + specular) * objectColor;
  fragColor = vec4(result, 1.0); //final result
}