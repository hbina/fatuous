#pragma once

struct Intensity
{
    float m_attval = 1.0f;
    float m_constant = 1.0f;
    float m_linear = 1.0f;
    float m_quadratic = 1.0f;
    Intensity() = delete;
    Intensity(
        const float attval,
        const float constant,
        const float linear,
        const float quadr);
};
