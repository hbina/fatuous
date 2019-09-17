#include "components/phong_light.hpp"

PhongLight::PhongLight(
    const glm::vec3 &p_ambient,
    const glm::vec3 &p_diffuse,
    const glm::vec3 &p_specular)
    : m_ambient(p_ambient),
      m_diffuse(p_diffuse),
      m_specular(p_specular) {}
