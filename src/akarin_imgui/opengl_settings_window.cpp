#include "akarin_imgui/opengl_settings_window.hpp"
#include "misc/opengl_settings.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <array>
#include <iostream>

bool enable_depth_testing = true;
bool enable_face_culling = true;

void OpenGLSettingsWindow::render() noexcept
{
    ImGui::Begin("OpenGL Settings");

    if (ImGui::CollapsingHeader("Depth Testing"))
    {
        constexpr std::array<const char *, 8> depth_function_names = {
            "ALWAYS",
            "NEVER",
            "LESS",
            "EQUAL",
            "LEQUAL",
            "GREATER",
            "NOTEQUAL",
            "GEQUAL",
        };

        ImGui::Checkbox("Enable##depth_testing", &enable_depth_testing);
        OpenGLSettings::enable(GLEnum::DEPTH_TEST, enable_depth_testing);
        static int depth_func_idx = 2;
        ImGui::Combo(
            "Depth Test Function",
            &depth_func_idx,
            depth_function_names.data(),
            static_cast<int>(depth_function_names.size()));
        OpenGLSettings::set_depth_function(static_cast<DepthFun>(depth_func_idx));
    }

    if (ImGui::CollapsingHeader("Face Culling"))
    {
        constexpr std::array<const char *, 3> cull_face_names = {
            "FRONT",
            "BACK",
            "FRONT_AND_BACK",
        };

        ImGui::Checkbox("Enable##cull_face", &enable_face_culling);
        OpenGLSettings::enable(GLEnum::CULL_FACE, enable_face_culling);
        static int cull_face_idx = 1;
        ImGui::Combo(
            "Cull Face",
            &cull_face_idx,
            cull_face_names.data(),
            static_cast<int>(cull_face_names.size()));
        OpenGLSettings::set_cull_face(static_cast<CullFace>(cull_face_idx));
    }

    ImGui::End();
};