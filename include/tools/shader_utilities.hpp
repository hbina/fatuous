#ifndef SHADER_UTILITIES_HPP
#define SHADER_UTILITIES_HPP

#include "glm/glm.hpp"

#include <string>
#include <array>

namespace ShaderUtilities
{
void use(
    const std::size_t) noexcept;

void transform_shader(
    const std::size_t,
    const glm::mat4 &,
    const glm::mat4 &,
    const glm::vec3 &,
    const glm::vec3 &p_scale) noexcept;

void setBool(
    const std::size_t,
    const std::string &,
    const bool) noexcept;

void setInt(
    const std::size_t,
    const std::string &,
    const int) noexcept;

void setFloat(
    const std::size_t,
    const std::string &,
    const float) noexcept;

void setVec2(
    const std::size_t,
    const std::string &,
    const glm::vec2 &) noexcept;

void setVec2(
    const std::size_t,
    const std::string &,
    const std::array<float, 2> &) noexcept;

void setVec3(
    const std::size_t,
    const std::string &,
    const glm::vec3 &) noexcept;

void setVec3(
    const std::size_t,
    const std::string &,
    const std::array<float, 3> &) noexcept;

void setVec4(
    const std::size_t,
    const std::string &,
    const glm::vec4 &) noexcept;

void setVec4(
    const std::size_t,
    const std::string &,
    const std::array<float, 4> &) noexcept;

void setMat2(
    const std::size_t,
    const std::string &,
    const glm::mat2 &) noexcept;

void setMat3(
    const std::size_t,
    const std::string &,
    const glm::mat3 &) noexcept;

void setMat4(
    const std::size_t,
    const std::string &,
    const glm::mat4 &) noexcept;

}; // namespace ShaderUtilities

#endif
