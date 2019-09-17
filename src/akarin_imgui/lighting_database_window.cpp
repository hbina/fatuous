#include "akarin_imgui/lighting_database_window.hpp"
#include "akarin_database/glfw/akarin_glfw.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <array>
#include <sstream>

// Shadow stuff
float LightingDbWindow::shadow_bias = 0.1f;
float LightingDbWindow::near_plane = 1.0f;
float LightingDbWindow::far_plane = 1000.0f;

bool LightingDbWindow::enable_shadow = true;
bool LightingDbWindow::enable_directional_light = true;
bool LightingDbWindow::enable_point_light = true;
bool LightingDbWindow::enable_spot_light = true;

void LightingDbWindow::render() noexcept
{
    ImGui::Begin("Lighting Database");
    if (ImGui::CollapsingHeader("Shadow Properties"))
    {
        ImGui::Checkbox("Enable Shadow", &enable_shadow);
        ImGui::SliderFloat("shadow_bias##shadow", &shadow_bias, 1.0f, 25.0f);
        ImGui::SliderFloat("near_plane##shadow", &near_plane, 1.0f, 100.0f);
        ImGui::SliderFloat("far_plane##shadow", &far_plane, 100.0f, 1000.0f);
    }
    if (ImGui::CollapsingHeader("Directional Light Database"))
    {
        ImGui::Checkbox("Enable##directional_light", &enable_directional_light);
        if (ImGui::Button("Create##directional_light"))
        {
            LightingDb::create_dir_light();
        }
        for (std::pair<const std::size_t, DirectionalLight> &p_iter : LightingDb::dir_map)
        {
            std::stringstream ostr_id;
            ostr_id << "id:" << p_iter.first;
            if (ImGui::TreeNode(ostr_id.str().c_str()))
            {
                auto &directional_light = p_iter.second;
                ImGui::SliderFloat("shininess##directional_light", &directional_light.m_shininess, 0.0f, 128.0f);
                ImGui::SliderFloat3("direction##directional_light", &directional_light.m_direction.x, -1.0f, 1.0f);
                ImGui::ColorEdit3("ambient##directional_light", &directional_light.m_phong.m_ambient.x);
                ImGui::ColorEdit3("diffuse##directional_light", &directional_light.m_phong.m_ambient.x);
                ImGui::ColorEdit3("specular##directional_light", &directional_light.m_phong.m_ambient.x);
                ImGui::TreePop();
            }
        }
    }

    if (ImGui::CollapsingHeader("Point Light Database"))
    {
        ImGui::Checkbox("Enable##point_light", &enable_point_light);
        if (ImGui::Button("Create##point_light"))
        {
            LightingDb::create_point_light();
        }
        for (std::pair<const std::size_t, PointLight> &p_iter : LightingDb::point_map)
        {
            std::stringstream ostr_id;
            ostr_id << "id:" << p_iter.first;
            if (ImGui::TreeNode(ostr_id.str().c_str()))
            {
                auto &point_light = p_iter.second;
                ImGui::SliderFloat3("position##point_light", &point_light.m_pos.x, -500.0f, 500.0f);
                ImGui::SliderFloat("attenuation_value##point_light", &point_light.m_intensity.m_attval, 1.0f, 100.0f);
                ImGui::SliderFloat("constant##point_light", &point_light.m_intensity.m_const, 1.0f, 100.0f);
                ImGui::SliderFloat("linear##point_light", &point_light.m_intensity.m_linear, 0.1f, 10.0f);
                ImGui::SliderFloat("quadratic##point_light", &point_light.m_intensity.m_quadr, 0.001f, 0.100f);
                ImGui::ColorEdit3("ambient##point_light", &point_light.m_phong.m_ambient.x);
                ImGui::ColorEdit3("diffuse##point_light", &point_light.m_phong.m_diffuse.x);
                ImGui::ColorEdit3("specular##point_light", &point_light.m_phong.m_specular.x);
                ImGui::TreePop();
            }
        }
    }

    if (ImGui::CollapsingHeader("Spot Light Database"))
    {
        ImGui::Checkbox("Enable##spot_light", &enable_spot_light);
        if (ImGui::Button("Create##spot_light"))
        {
            LightingDb::create_spot_light();
        }
        for (std::pair<const std::size_t, SpotLight> &p_iter : LightingDb::spot_map)
        {
            std::stringstream ostr_id;
            ostr_id << "id:" << p_iter.first;
            if (ImGui::TreeNode(ostr_id.str().c_str()))
            {
                auto &spot_light = p_iter.second;
                ImGui::InputFloat("cutOff##spot_light", &spot_light.cutOff);
                ImGui::InputFloat("outerCutOff##spot_light", &spot_light.outerCutOff);
                ImGui::InputFloat("attenuation_value##spot_light", &spot_light.m_intensity.m_attval);
                ImGui::InputFloat("constant##spot_light", &spot_light.m_intensity.m_const);
                ImGui::InputFloat("linear##spot_light", &spot_light.m_intensity.m_linear);
                ImGui::InputFloat("quadratic##spot_light", &spot_light.m_intensity.m_quadr);
                ImGui::ColorEdit3("ambient##spot_light", &spot_light.m_phong.m_ambient.x);
                ImGui::ColorEdit3("diffuse##spot_light", &spot_light.m_phong.m_diffuse.x);
                ImGui::ColorEdit3("specular##spot_light", &spot_light.m_phong.m_specular.x);
                ImGui::TreePop();
            }
        }
    }

    ImGui::End();
};
