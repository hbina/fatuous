#include "components/lighting.hpp"

DirectionalLight::DirectionalLight(
    const std::array<float, 3> &p_direction,
    const PhongLight &p_phong)
    : m_direction(p_direction),
      m_phong(p_phong){};
