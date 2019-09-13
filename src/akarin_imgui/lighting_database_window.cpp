#include "akarin_imgui/lighting_database_window.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <array>

float LightingDbWindow::shadow_bias = 0.1;

bool LightingDbWindow::enable_shadow = true;
bool LightingDbWindow::enable_directional_light = true;
bool LightingDbWindow::enable_point_light = true;
bool LightingDbWindow::enable_spot_light = true;

DirectionalLight LightingDbWindow::directional_light;
PointLight LightingDbWindow::point_light;
SpotLight LightingDbWindow::spot_light;

void LightingDbWindow::render() noexcept
{
    ImGui::Begin("Lighting System");
    ImGui::Checkbox("Enable Shadow", &enable_shadow);
    ImGui::SliderFloat("shadow_bias", &shadow_bias, 0.0f, 1.0f);
    if (ImGui::CollapsingHeader("Directional Light Properties"))
    {
        ImGui::Checkbox("Enable##directional_light", &enable_directional_light);
        ImGui::SliderFloat("shininess##directional_light", &directional_light.shininess, 0.0f, 128.0f);
        ImGui::SliderFloat3("direction##directional_light", directional_light.direction.data(), -1.0f, 1.0f);
        ImGui::ColorEdit3("ambient##directional_light", directional_light.ambient.data());
        ImGui::ColorEdit3("diffuse##directional_light", directional_light.diffuse.data());
        ImGui::ColorEdit3("specular##directional_light", directional_light.specular.data());
    }

    if (ImGui::CollapsingHeader("Point Light Properties"))
    {
        ImGui::Checkbox("Enable##point_light", &enable_point_light);
        ImGui::SliderFloat3("position##point_light", point_light.position.data(), -500.0f, 500.0f);
        ImGui::SliderFloat("constant##point_light", &point_light.constant, 0.1f, 1.0f);
        ImGui::SliderFloat("linear##point_light", &point_light.linear, 0.01f, 0.10f);
        ImGui::SliderFloat("quadratic##point_light", &point_light.quadratic, 0.001f, 0.010f);
        ImGui::ColorEdit3("ambient##point_light", point_light.ambient.data());
        ImGui::ColorEdit3("diffuse##point_light", point_light.diffuse.data());
        ImGui::ColorEdit3("specular##point_light", point_light.specular.data());
    }

    if (ImGui::CollapsingHeader("Spot Light Properties"))
    {
        ImGui::Checkbox("Enable##spot_light", &enable_spot_light);
        ImGui::InputFloat("cutOff##spot_light", &spot_light.cutOff);
        ImGui::InputFloat("outerCutOff##spot_light", &spot_light.outerCutOff);
        ImGui::InputFloat("constant##spot_light", &spot_light.constant);
        ImGui::InputFloat("linear##spot_light", &spot_light.linear);
        ImGui::InputFloat("quadratic##spot_light", &spot_light.quadratic);
        ImGui::ColorEdit3("ambient##spot_light", spot_light.ambient.data());
        ImGui::ColorEdit3("diffuse##spot_light", spot_light.diffuse.data());
        ImGui::ColorEdit3("specular##spot_light", spot_light.specular.data());
    }

    ImGui::End();
};
