#include "components/vertex.hpp"

Vertex::Vertex(
    const glm::vec3 &p_position,
    const glm::vec3 &p_normal,
    const glm::vec3 &p_tangent,
    const glm::vec3 &p_bitangent,
    const glm::vec2 &p_tex_coord)
    : m_position(p_position),
      m_normal(p_normal),
      m_tangent(p_tangent),
      m_bitangent(p_bitangent),
      m_tex_coord(p_tex_coord){};
