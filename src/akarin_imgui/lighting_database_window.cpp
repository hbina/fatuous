#include "akarin_imgui/lighting_database_window.hpp"


#include "imgui/imgui.h"
#include "imgui/examples/imgui_impl_glfw.h"
#include "imgui/examples/imgui_impl_opengl3.h"

#include <array>

bool LightingDatabaseWindow::enable_directional_light = true;
bool LightingDatabaseWindow::enable_point_light = true;
bool LightingDatabaseWindow::enable_spot_light = true;

DirectionalLight LightingDatabaseWindow::directional_light;
PointLight LightingDatabaseWindow::point_light;
SpotLight LightingDatabaseWindow::spot_light;

void LightingDatabaseWindow::render() noexcept
{
    ImGui::Begin("Lighting System");

    if (ImGui::CollapsingHeader("Directional Light Properties"))
    {
        ImGui::Checkbox("Enable Directional Light", &enable_directional_light);
        ImGui::SliderFloat("shininess#A", &directional_light.shininess, 0.0f, 128.0f);
        ImGui::SliderFloat3("direction#A", directional_light.direction.data(), -1.0f, 1.0f);
        ImGui::ColorEdit3("ambient#A", directional_light.ambient.data());
        ImGui::ColorEdit3("diffuse#A", directional_light.diffuse.data());
        ImGui::ColorEdit3("specular#A", directional_light.specular.data());
    }

    if (ImGui::CollapsingHeader("Point Light Properties"))
    {
        ImGui::Checkbox("Enable Point Light", &enable_point_light);
        ImGui::SliderFloat3("position#B", point_light.position.data(), -500.0f, 500.0f);
        ImGui::SliderFloat("constant#B", &point_light.constant, 0.1f, 1.0f);
        ImGui::SliderFloat("linear#B", &point_light.linear, 0.01f, 0.10f);
        ImGui::SliderFloat("quadratic#B", &point_light.quadratic, 0.001f, 0.010f);
        ImGui::ColorEdit3("ambient#B", point_light.ambient.data());
        ImGui::ColorEdit3("diffuse#B", point_light.diffuse.data());
        ImGui::ColorEdit3("specular#B", point_light.specular.data());
    }

    if (ImGui::CollapsingHeader("Spot Light Properties"))
    {
        ImGui::Checkbox("Enable Spot Light", &enable_spot_light);
        ImGui::InputFloat("cutOff#C", &spot_light.cutOff);
        ImGui::InputFloat("outerCutOff#C", &spot_light.outerCutOff);
        ImGui::InputFloat("constant#C", &spot_light.constant);
        ImGui::InputFloat("linear#C", &spot_light.linear);
        ImGui::InputFloat("quadratic#C", &spot_light.quadratic);
        ImGui::ColorEdit3("ambient#C", spot_light.ambient.data());
        ImGui::ColorEdit3("diffuse#C", spot_light.diffuse.data());
        ImGui::ColorEdit3("specular#C", spot_light.specular.data());
    }

    ImGui::End();
};
