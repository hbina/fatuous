#include "components/intensity.hpp"

Intensity::Intensity(
    const float p_attval,
    const float p_constant,
    const float p_linear,
    const float p_quadratic)
    : m_attval(p_attval),
      m_constant(p_constant),
      m_linear(p_linear),
      m_quadratic(p_quadratic){};
