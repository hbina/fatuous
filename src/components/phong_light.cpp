#include "components/phong_light.hpp"

PhongLight::PhongLight(
    const std::array<float, 3> &p_ambient,
    const std::array<float, 3> &p_diffuse,
    const std::array<float, 3> &p_specular)
    : m_ambient(p_ambient),
      m_diffuse(p_diffuse),
      m_specular(p_specular){};
