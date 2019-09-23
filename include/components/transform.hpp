#pragma once

#include "glm/glm.hpp"

struct Transform
{
    glm::vec3 m_position;
    glm::vec3 m_scale;

    Transform() = delete;
    Transform(
        const glm::vec3 &p_position,
        const glm::vec3 &p_scale);
};
