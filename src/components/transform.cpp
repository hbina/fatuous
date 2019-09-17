#include "components/transform.hpp"

Transform::Transform(
    const glm::vec3 &p_position,
    const glm::vec3 &p_scale)
    : m_position(p_position),
      m_scale(p_scale){};
