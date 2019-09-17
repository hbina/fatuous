#pragma once

#include "glm/glm.hpp"

struct PhongLight
{
    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;

    PhongLight() = delete;
    PhongLight(
        const glm::vec3 &,
        const glm::vec3 &,
        const glm::vec3 &);
};
