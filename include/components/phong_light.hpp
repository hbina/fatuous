#pragma once

#include <array>

struct PhongLight
{
    std::array<float, 3> m_ambient = {0.1f, 0.1f, 0.1f};
    std::array<float, 3> m_diffuse = {1.0f, 1.0f, 1.0f};
    std::array<float, 3> m_specular = {0.1f, 0.1f, 0.1f};
    PhongLight() = delete;
    PhongLight(
        const std::array<float, 3> &p_ambient,
        const std::array<float, 3> &p_diffuse,
        const std::array<float, 3> &p_specular);
};
