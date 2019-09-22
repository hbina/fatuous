#pragma once

struct Intensity
{
    float m_attval = 25.0f;
    float m_constant = 0.5f;
    float m_linear = 0.01f;
    float m_quadratic = 0.03f;
    Intensity() = delete;
    Intensity(
        const float attval,
        const float constant,
        const float linear,
        const float quadr);
};
