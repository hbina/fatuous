#include "components/lighting.hpp"

DirectionalLight::DirectionalLight(
    const float p_shininess,
    const glm::vec3 &p_direction,
    const PhongLight &p_phong)
    : m_shininess(p_shininess),
      m_direction(p_direction),
      m_phong(p_phong){};

PointLight::PointLight(
    const glm::vec3 &p_pos,
    const Intensity &p_intensity,
    const PhongLight &p_phong,
    const DepthBuffer &p_buffer)
    : m_pos(p_pos),
      m_intensity(p_intensity),
      m_phong(p_phong),
      m_buffer(p_buffer){};

SpotLight::SpotLight(
    const glm::vec3 &p_pos,
    const glm::vec3 &p_direction,
    const float p_cutOff,
    const float p_outerCutOff,
    const Intensity &p_intensity,
    const PhongLight &p_phong)
    : m_pos(p_pos),
      m_direction(p_direction),
      cutOff(p_cutOff),
      outerCutOff(p_outerCutOff),
      m_intensity(p_intensity),
      m_phong(p_phong){};
