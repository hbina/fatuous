#pragma once

struct Intensity
{
    float m_attval;
    float m_constant;
    float m_linear;
    float m_quadratic;
    Intensity() = delete;
    Intensity(
        const float attval,
        const float constant,
        const float linear,
        const float quadr);
};
