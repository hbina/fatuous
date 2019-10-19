#ifndef SHADER_UTILITIES_HPP
#define SHADER_UTILITIES_HPP

#include "components/lighting.hpp"

#include "glm/glm.hpp"
#include "glad/glad.h"

#include <string>
#include <array>

namespace ShaderUtilities
{
void use(
    const GLuint) noexcept;

void transform_shader(
    const GLuint,
    const glm::mat4 &,
    const glm::mat4 &,
    const glm::vec3 &,
    const glm::vec3 &,
    const bool draw_depth = false) noexcept;

void attach_dir_light(
    const GLuint p_shader_id,
    const DirectionalLight &directional_light) noexcept;

void attach_point_light(
    const GLuint p_shader_id,
    const PointLight &point_light) noexcept;

void attach_spot_light(
    const GLuint p_shader_id,
    const SpotLight &spot_light) noexcept;

void setBool(
    const GLuint,
    const std::string &,
    const bool) noexcept;

void setInt(
    const GLuint,
    const std::string &,
    const int) noexcept;

void setFloat(
    const GLuint,
    const std::string &,
    const float) noexcept;

void setVec2(
    const GLuint,
    const std::string &,
    const glm::vec2 &) noexcept;

void setVec2(
    const GLuint,
    const std::string &,
    const std::array<float, 2> &) noexcept;

void setVec3(
    const GLuint,
    const std::string &,
    const glm::vec3 &) noexcept;

void setVec3(
    const GLuint,
    const std::string &,
    const std::array<float, 3> &) noexcept;

void setVec4(
    const GLuint,
    const std::string &,
    const glm::vec4 &) noexcept;

void setVec4(
    const GLuint,
    const std::string &,
    const std::array<float, 4> &) noexcept;

void setMat2(
    const GLuint,
    const std::string &,
    const glm::mat2 &) noexcept;

void setMat3(
    const GLuint,
    const std::string &,
    const glm::mat3 &) noexcept;

void setMat4(
    const GLuint,
    const std::string &,
    const glm::mat4 &) noexcept;

}; // namespace ShaderUtilities

#endif
