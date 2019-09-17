#pragma once

struct Intensity
{
    float m_attval;
    float m_const;
    float m_linear;
    float m_quadr;

    Intensity() = delete;
    Intensity(
        const float,
        const float,
        const float,
        const float);
};
