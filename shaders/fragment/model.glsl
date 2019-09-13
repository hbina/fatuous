#version 330 core
out vec4 FragColor;

struct Material {
  sampler2D diffuse;
  sampler2D specular;
  sampler2D normal;
  sampler2D height;
  float shininess;
};

struct DirectionalLight {
  vec3 direction;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

struct PointLight {
  vec3 position;
  float constant;
  float linear;
  float quadratic;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

struct SpotLight {
  vec3 position;
  vec3 direction;
  float cutOff;
  float outerCutOff;
  float constant;
  float linear;
  float quadratic;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
in mat3 TBN;

uniform vec3 camera_position;
uniform DirectionalLight directional_light;
uniform PointLight point_light;
uniform SpotLight spot_light;
uniform Material material;
uniform samplerCube depth_map;
uniform float far_plane;
uniform vec3 light_pos;

// function prototypes
vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 view_direction);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos,
                    vec3 view_direction);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos,
                   vec3 view_direction);
float ShadowCalculation(vec3 fragPos);

void main() {
  vec4 textureColour = texture(material.diffuse, TexCoords);
  if (textureColour.a < 0.5) {
    discard;
  }
  // properties
  vec3 normal = texture(material.normal, TexCoords).rgb;
  normal = normalize(normal * 2.0 - 1.0);
  normal = normalize(TBN * normal);

  // vec3 norm = normalize(Normal);
  vec3 view_direction = normalize(camera_position - FragPos);
  float shadow = ShadowCalculation(FragPos);
  vec3 result = CalcDirLight(directional_light, normal, view_direction);
  result += (1.0 - shadow) *
            CalcPointLight(point_light, normal, FragPos, view_direction);
  result += (1.0 - shadow) *
            CalcSpotLight(spot_light, normal, FragPos, view_direction);
  FragColor = vec4(result, 1.0);
}

// calculates the color when using a directional light.
vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 view_direction) {
  vec3 light_direction = normalize(-light.direction);
  // diffuse shading
  float diff = max(dot(normal, light_direction), 0.0);
  // specular shading
  vec3 reflect_direction = reflect(-light_direction, normal);
  float spec =
      pow(max(dot(view_direction, reflect_direction), 0.0), material.shininess);
  // combine results
  vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
  vec3 diffuse =
      light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
  vec3 specular =
      light.specular * spec * vec3(texture(material.specular, TexCoords));
  return (ambient + diffuse + specular);
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos,
                    vec3 view_direction) {
  vec3 light_direction = normalize(light.position - fragPos);
  // diffuse shading
  float diff = max(dot(normal, light_direction), 0.0);
  // specular shading
  vec3 reflect_direction = reflect(-light_direction, normal);
  float spec =
      pow(max(dot(view_direction, reflect_direction), 0.0), material.shininess);
  // attenuation
  float distance = length(light.position - fragPos);
  float attenuation = 1.0 / (light.constant + light.linear * distance +
                             light.quadratic * (distance * distance));
  // combine results
  vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
  vec3 diffuse =
      light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
  vec3 specular =
      light.specular * spec * vec3(texture(material.specular, TexCoords));
  ambient *= attenuation;
  diffuse *= attenuation;
  specular *= attenuation;
  return (ambient + diffuse + specular);
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos,
                   vec3 view_direction) {
  vec3 light_direction = normalize(light.position - fragPos);
  // diffuse shading
  float diff = max(dot(normal, light_direction), 0.0);
  // specular shading
  vec3 reflect_direction = reflect(-light_direction, normal);
  float spec =
      pow(max(dot(view_direction, reflect_direction), 0.0), material.shininess);
  // attenuation
  float distance = length(light.position - fragPos);
  float attenuation = 1.0 / (light.constant + light.linear * distance +
                             light.quadratic * (distance * distance));
  // spotlight intensity
  float theta = dot(light_direction, normalize(-light.direction));
  float epsilon = light.cutOff - light.outerCutOff;
  float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
  // combine results
  vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
  vec3 diffuse =
      light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
  vec3 specular =
      light.specular * spec * vec3(texture(material.specular, TexCoords));
  ambient *= attenuation * intensity;
  diffuse *= attenuation * intensity;
  specular *= attenuation * intensity;
  return (ambient + diffuse + specular);
}

float ShadowCalculation(vec3 fragPos) {
  // get vector between fragment position and light position
  vec3 fragToLight = fragPos - light_pos;
  // use the light to fragment vector to sample from the depth map
  float closestDepth = texture(depth_map, fragToLight).r;
  // it is currently in linear range between [0,1]. Re-transform back to
  // original value
  closestDepth *= far_plane;
  // now get current linear depth as the length between the fragment and light
  // position
  float currentDepth = length(fragToLight);
  // now test for shadows
  float bias = 0.05;
  float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

  return shadow;
}