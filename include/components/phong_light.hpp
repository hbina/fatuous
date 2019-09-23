#pragma once

#include "glm/glm.hpp"

#include <array>

struct PhongLight
{
    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;
    PhongLight() = delete;
    PhongLight(
        const glm::vec3 &p_ambient,
        const glm::vec3 &p_diffuse,
        const glm::vec3 &p_specular);
};
