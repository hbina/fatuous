#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;
layout(location = 3) in vec3 aTangent;
layout(location = 4) in vec3 aBitangent;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;
out vec3 Position;

uniform mat4 projection_view_model;
uniform mat4 model;

void main() {
  FragPos = vec3(model * vec4(aPos, 1.0));
  Normal = mat3(transpose(inverse(model))) * aNormal;
  TexCoords = aTexCoords;
  Position = vec3(model * vec4(aPos, 1.0));
  gl_Position = projection_view_model * vec4(aPos, 1.0);
}
