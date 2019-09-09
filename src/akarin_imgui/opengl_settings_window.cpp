#include "akarin_imgui/opengl_settings_window.hpp"

#include "misc/opengl_settings.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <array>
#include <iostream>

bool enable_depth_testing = false;

void OpenGLSettingsWindow::render() noexcept
{
    ImGui::Begin("OpenGL Settings");

    if (ImGui::CollapsingHeader("Depth Test"))
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
        static int item_current = 0;
        ImGui::Combo(
            "Depth Test Function",
            &item_current,
            depth_function_names.data(),
            depth_function_names.size());
        OpenGLSettings::set_depth_function(static_cast<DepthFun>(item_current));
    }

    ImGui::End();
};