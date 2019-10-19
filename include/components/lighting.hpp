#pragma once

#include "phong_light.hpp"
#include "intensity.hpp"
#include "depth_buffer.hpp"

#include "glm/glm.hpp"

#include <array>

// Move this out to a shader class or something
struct DirectionalLight
{
    float m_shininess;
    glm::vec3 m_direction;
    PhongLight m_phong;

    DirectionalLight() = delete;
    DirectionalLight(
        const float p_shininess,
        const glm::vec3 &p_direction,
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
        const PhongLight &p_phong,
        const DepthBuffer &p_buffer);
};

struct SpotLight
{
    // These stuff are unique to SpotLight ... for now
    glm::vec2 m_radial;
    glm::vec3 m_direction;
    Intensity m_intensity;
    PhongLight m_phong;
    SpotLight() = delete;
    SpotLight(
        const glm::vec2 &p_radial,
        const glm::vec3 &p_direction,
        const Intensity &p_intensity,
        const PhongLight &p_phong);
};
