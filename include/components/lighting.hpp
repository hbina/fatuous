#pragma once

#include "phong_light.hpp"
#include "intensity.hpp"
#include "depth_buffer.hpp"

#include "glm/glm.hpp"

#include <array>

// Move this out to a shader class or something
struct DirectionalLight
{
    float m_shininess = 32.0f;
    std::array<float, 3> m_direction = {0.0f, 1.0f, 0.0f};
    // std::array<float, 3> ambient = {0.1f, 0.1f, 0.1f};
    // std::array<float, 3> diffuse = {1.0f, 1.0f, 1.0f};
    // std::array<float, 3> specular = {0.1f, 0.1f, 0.1f};
    PhongLight m_phong;

    DirectionalLight() = delete;
    DirectionalLight(
        const std::array<float, 3> &p_direction,
        const PhongLight &p_phong);
};

struct PointLight
{
    glm::vec3 m_position;
    Intensity m_intensity;
    PhongLight m_phong;
    DepthBuffer m_buffer;
    PointLight() = delete;
    PointLight(
        const glm::vec3 &p_position,
        const Intensity &p_intensity,
        const PhongLight &p_phong);
};

struct SpotLight
{
    float cutOff = 12.5f;
    float outerCutOff = 15.0f;
    float attenuation_value = 25.0f;
    float constant = 0.5f;
    float linear = 0.01f;
    float quadratic = 0.003f;
    std::array<float, 3> ambient = {1.0f, 1.0f, 1.0f};
    std::array<float, 3> diffuse = {1.0f, 1.0f, 1.0f};
    std::array<float, 3> specular = {1.0f, 1.0f, 1.0f};
};
