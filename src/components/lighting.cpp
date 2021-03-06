#include "components/lighting.hpp"

DirectionalLight::DirectionalLight(
    const glm::vec3 &p_direction,
    const PhongLight &p_phong)
    : m_direction(p_direction),
      m_phong(p_phong){};

PointLight::PointLight(
    const glm::vec3 &p_position,
    const Intensity &p_intensity,
    const PhongLight &p_phong,
    const DepthBuffer &p_buffer)
    : m_position(p_position),
      m_intensity(p_intensity),
      m_phong(p_phong),
      m_buffer(p_buffer){};
