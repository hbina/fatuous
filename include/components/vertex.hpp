#pragma once

#include "glm/glm.hpp"

struct Vertex
{
    const glm::vec3 m_position;
    const glm::vec3 m_normal;
    const glm::vec3 m_tangent;
    const glm::vec3 m_bitangent;
    const glm::vec2 m_tex_coord;

    Vertex() = delete;
    Vertex(
        const glm::vec3 &p_position,
        const glm::vec3 &p_normal,
        const glm::vec3 &p_tangent,
        const glm::vec3 &p_bitangent,
        const glm::vec2 &p_tex_coord);
};
