#include "akarin_imgui/lighting_database_window.hpp"
#include "akarin_database/lighting/lighting_database.hpp"
#include "akarin_database/glfw/akarin_glfw.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <sstream>
#include <array>

// Shadow stuff
float LightingDbWindow::shadow_bias = 1.0f;
float LightingDbWindow::near_plane = 1.0f;
float LightingDbWindow::far_plane = 1000.0f;

bool LightingDbWindow::enable_shadow = true;
bool LightingDbWindow::enable_shadow_debug = false;

bool LightingDbWindow::enable_dir_light = true;
bool LightingDbWindow::enable_point_light = true;
bool LightingDbWindow::enable_spot_light = true;

void LightingDbWindow::render() noexcept
{
    ImGui::Begin("Lighting Database");
    if (ImGui::CollapsingHeader("Shadow Properties"))
    {
        ImGui::Checkbox("Enable Shadow", &enable_shadow);
        ImGui::Checkbox("Enable Shadow Debug", &enable_shadow_debug);
        ImGui::SliderFloat("shadow_bias##shadow", &shadow_bias, 0.0f, 25.0f);
        ImGui::SliderFloat("near_plane##shadow", &near_plane, 0.0f, 100.0f);
        ImGui::SliderFloat("far_plane##shadow", &far_plane, 100.0f, 1000.0f);
    }
    if (ImGui::CollapsingHeader("Directional Light Properties"))
    {
        ImGui::Checkbox("Enable##directional_light", &enable_dir_light);
        for (auto &iter : LightingDb::dir_map)
        {
            std::stringstream dir_ostr;
            dir_ostr << iter.first;
            dir_ostr << "##directional_light";
            if (ImGui::TreeNode(dir_ostr.str().c_str()))
            {
                ImGui::SliderFloat("shininess##directional_light", &iter.second.m_shininess, 0.0f, 128.0f);
                ImGui::SliderFloat3("direction##directional_light", &iter.second.m_direction[0], -1.0f, 1.0f);
                ImGui::ColorEdit3("ambient##directional_light", &iter.second.m_phong.m_ambient[0]);
                ImGui::ColorEdit3("diffuse##directional_light", &iter.second.m_phong.m_diffuse[0]);
                ImGui::ColorEdit3("specular##directional_light", &iter.second.m_phong.m_specular[0]);
                ImGui::TreePop();
            }
        }
    }
    if (ImGui::CollapsingHeader("Point Light Properties"))
    {
        ImGui::Checkbox("Enable##point_light", &enable_point_light);
        for (auto &iter : LightingDb::point_map)
        {
            std::stringstream point_ostr;
            point_ostr << iter.first;
            point_ostr << "##point_light";
            if (ImGui::TreeNode(point_ostr.str().c_str()))
            {
                ImGui::SliderFloat3("position##point_light", &iter.second.m_position[0], -500.0f, 500.0f);
                ImGui::SliderFloat("attenuation_value##point_light", &iter.second.m_intensity.m_attval, 1.0f, 100.0f);
                ImGui::SliderFloat("constant##point_light", &iter.second.m_intensity.m_constant, 1.0f, 100.0f);
                ImGui::SliderFloat("linear##point_light", &iter.second.m_intensity.m_linear, 0.1f, 10.0f);
                ImGui::SliderFloat("quadratic##point_light", &iter.second.m_intensity.m_quadratic, 0.001f, 0.100f);
                ImGui::ColorEdit3("ambient##point_light", &iter.second.m_phong.m_ambient[0]);
                ImGui::ColorEdit3("diffuse##point_light", &iter.second.m_phong.m_diffuse[0]);
                ImGui::ColorEdit3("specular##point_light", &iter.second.m_phong.m_specular[0]);
                ImGui::TreePop();
            }
        }
    }
    if (ImGui::CollapsingHeader("Spot Light Properties"))
    {
        ImGui::Checkbox("Enable##spot_light", &enable_spot_light);
        for (auto &iter : LightingDb::spot_map)
        {
            std::stringstream spot_ostr;
            spot_ostr << iter.first;
            spot_ostr << "##spot_light";
            if (ImGui::TreeNode(spot_ostr.str().c_str()))
            {
                ImGui::InputFloat("cutOff##spot_light", &iter.second.m_radial.x);
                ImGui::InputFloat("outerCutOff##spot_light", &iter.second.m_radial.y);
                ImGui::InputFloat("attenuation_value##spot_light", &iter.second.m_intensity.m_attval);
                ImGui::InputFloat("constant##spot_light", &iter.second.m_intensity.m_constant);
                ImGui::InputFloat("linear##spot_light", &iter.second.m_intensity.m_linear);
                ImGui::InputFloat("quadratic##spot_light", &iter.second.m_intensity.m_quadratic);
                ImGui::ColorEdit3("ambient##spot_light", &iter.second.m_phong.m_ambient[0]);
                ImGui::ColorEdit3("diffuse##spot_light", &iter.second.m_phong.m_diffuse[0]);
                ImGui::ColorEdit3("specular##spot_light", &iter.second.m_phong.m_specular[0]);
            }
        }
    }
    ImGui::End();
};
