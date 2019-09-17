#include "components/intensity.hpp"

Intensity::Intensity(
    const float p_attval,
    const float p_const,
    const float p_linear,
    const float p_quadr)
    : m_attval(p_attval),
      m_const(p_const),
      m_linear(p_linear),
      m_quadr(p_quadr){};
