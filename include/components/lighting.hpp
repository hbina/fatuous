#pragma once

#include <array>

// Move this out to a shader class or something
struct DirectionalLight
{
    float shininess = 32.0f;
    std::array<float, 3> direction = {0.0f, 1.0f, 0.0f};
    std::array<float, 3> ambient = {0.1f, 0.1f, 0.1f};
    std::array<float, 3> diffuse = {1.0f, 1.0f, 1.0f};
    std::array<float, 3> specular = {0.1f, 0.1f, 0.1f};
};

struct PointLight
{
    std::array<float, 3> position = {1.0f, 1.0f, 1.0f};
    float attenuation_value = 25.0f;
    float constant = 0.5f;
    float linear = 0.01f;
    float quadratic = 0.03f;
    std::array<float, 3> ambient = {1.0f, 1.0f, 1.0f};
    std::array<float, 3> diffuse = {1.0f, 1.0f, 1.0f};
    std::array<float, 3> specular = {1.0f, 1.0f, 1.0f};
};

struct SpotLight
{
    float cutOff = 12.5f;
    float outerCutOff = 15.0f;
    float attenuation_value = 25.0f;
    float constant = 0.5f;
    float linear = 0.01f;
    float quadratic = 0.003f;
    std::array<float, 3> ambient = {1.0f, 1.0f, 1.0f};
    std::array<float, 3> diffuse = {1.0f, 1.0f, 1.0f};
    std::array<float, 3> specular = {1.0f, 1.0f, 1.0f};
};
