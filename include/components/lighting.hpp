#pragma once

#include "components/depth_buffer.hpp"
#include "components/phong_light.hpp"
#include "components/intensity.hpp"
#include "components/position.hpp"

#include <array>

// Move this out to a shader class or something
struct DirectionalLight
{
    float m_shininess;
    glm::vec3 m_direction;
    PhongLight m_phong;

    DirectionalLight() = delete;
    DirectionalLight(
        const float,
        const glm::vec3 &,
        const PhongLight &);
};

struct PointLight
{
    glm::vec3 m_pos;
    Intensity m_intensity;
    PhongLight m_phong;
    DepthBuffer m_buffer;

    PointLight() = delete;
    PointLight(
        const glm::vec3 &,
        const Intensity &,
        const PhongLight &,
        const DepthBuffer &);
};

struct SpotLight
{
    glm::vec3 m_pos;
    glm::vec3 m_direction;
    float cutOff;
    float outerCutOff;
    Intensity m_intensity;
    PhongLight m_phong;

    SpotLight() = delete;
    SpotLight(
        const glm::vec3 &,
        const glm::vec3 &,
        const float,
        const float,
        const Intensity &,
        const PhongLight &);
};
