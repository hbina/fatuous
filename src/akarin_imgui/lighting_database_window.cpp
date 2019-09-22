#include "akarin_imgui/lighting_database_window.hpp"
#include "akarin_database/glfw/akarin_glfw.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <array>

// Shadow stuff
float LightingDbWindow::shadow_bias = 0.1f;
float LightingDbWindow::near_plane = 1.0f;
float LightingDbWindow::far_plane = 1000.0f;

bool LightingDbWindow::enable_shadow = true;
bool LightingDbWindow::enable_directional_light = true;
bool LightingDbWindow::enable_point_light = true;
bool LightingDbWindow::enable_spot_light = true;

DirectionalLight LightingDbWindow::directional_light = DirectionalLight(
    {1.0f, 1.0f, 1.0f},
    PhongLight(
        {0.1f, 0.1f, 0.1f},
        {1.0f, 1.0f, 1.0f},
        {0.1f, 0.1f, 0.1f}));

PointLight LightingDbWindow::point_light = PointLight(
    {0.0f, 0.0f, 0.0f},
    Intensity(
        25.0f,
        0.5f, 0.01f, 0.03f),
    PhongLight(
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f}));

SpotLight LightingDbWindow::spot_light;

void LightingDbWindow::render() noexcept
{
    ImGui::Begin("Lighting System");
    if (ImGui::CollapsingHeader("Shadow Properties"))
    {
        ImGui::Checkbox("Enable Shadow", &enable_shadow);
        ImGui::SliderFloat("shadow_bias##shadow", &shadow_bias, 0.0f, 25.0f);
        ImGui::SliderFloat("near_plane##shadow", &near_plane, 0.0f, 100.0f);
        ImGui::SliderFloat("far_plane##shadow", &far_plane, 100.0f, 1000.0f);
    }
    if (ImGui::CollapsingHeader("Directional Light Properties"))
    {
        ImGui::Checkbox("Enable##directional_light", &enable_directional_light);
        ImGui::SliderFloat("shininess##directional_light", &directional_light.m_shininess, 0.0f, 128.0f);
        ImGui::SliderFloat3("direction##directional_light", directional_light.m_direction.data(), -1.0f, 1.0f);
        ImGui::ColorEdit3("ambient##directional_light", directional_light.m_phong.m_ambient.data());
        ImGui::ColorEdit3("diffuse##directional_light", directional_light.m_phong.m_diffuse.data());
        ImGui::ColorEdit3("specular##directional_light", directional_light.m_phong.m_specular.data());
    }

    if (ImGui::CollapsingHeader("Point Light Properties"))
    {
        ImGui::Checkbox("Enable##point_light", &enable_point_light);
        ImGui::SliderFloat3("position##point_light", point_light.m_position.data(), -500.0f, 500.0f);
        ImGui::SliderFloat("attenuation_value##point_light", &point_light.m_intensity.m_attval, 1.0f, 100.0f);
        ImGui::SliderFloat("constant##point_light", &point_light.m_intensity.m_constant, 1.0f, 100.0f);
        ImGui::SliderFloat("linear##point_light", &point_light.m_intensity.m_linear, 0.1f, 10.0f);
        ImGui::SliderFloat("quadratic##point_light", &point_light.m_intensity.m_quadratic, 0.001f, 0.100f);
        ImGui::ColorEdit3("ambient##point_light", point_light.m_phong.m_ambient.data());
        ImGui::ColorEdit3("diffuse##point_light", point_light.m_phong.m_diffuse.data());
        ImGui::ColorEdit3("specular##point_light", point_light.m_phong.m_specular.data());
    }

    if (ImGui::CollapsingHeader("Spot Light Properties"))
    {
        ImGui::Checkbox("Enable##spot_light", &enable_spot_light);
        ImGui::InputFloat("cutOff##spot_light", &spot_light.cutOff);
        ImGui::InputFloat("outerCutOff##spot_light", &spot_light.outerCutOff);
        ImGui::InputFloat("attenuation_value##spot_light", &spot_light.attenuation_value);
        ImGui::InputFloat("constant##spot_light", &spot_light.constant);
        ImGui::InputFloat("linear##spot_light", &spot_light.linear);
        ImGui::InputFloat("quadratic##spot_light", &spot_light.quadratic);
        ImGui::ColorEdit3("ambient##spot_light", spot_light.ambient.data());
        ImGui::ColorEdit3("diffuse##spot_light", spot_light.diffuse.data());
        ImGui::ColorEdit3("specular##spot_light", spot_light.specular.data());
    }

    ImGui::End();
};
