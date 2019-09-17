#include "akarin_imgui/model_database_window.hpp"
#include "akarin_database/model/model_database.hpp"

#include "akarin_database/mesh/mesh_database.hpp"

#include "akarin_database/texture/texture_database.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <algorithm>
#include <ostream>
#include <sstream>

void ModelDbWindow::render(
    entt::registry &p_reg) noexcept // We will use this to list users of ModelInfo
{
    ImGui::Begin("Model Database");
    if (ImGui::CollapsingHeader("Load Models"))
    {
        static char model_path_text[64] = "";
        ImGui::InputText("path:", model_path_text, 64);
        if (ImGui::Button("Load Model"))
        {
            ModelDb::parse_model_file(
                std::string(model_path_text));
        }
    }
    if (ImGui::CollapsingHeader("Models List"))
    {
        for (const auto &p_modeldata_iter : ModelDb::map)
        {
            std::ostringstream modeldata_ostr;
            modeldata_ostr << p_modeldata_iter.first << " : ";
            modeldata_ostr << p_modeldata_iter.second.m_path;
            ImGui::Text("%s", modeldata_ostr.str().c_str());
        };
    }

    if (ImGui::CollapsingHeader("Meshes List"))
    {
        for (const std::pair<const std::size_t, Mesh> &mesh_iter : MeshDb::meshes_map)
        {
            const Mesh &mesh = mesh_iter.second;
            std::stringstream vao_id_ostr;
            vao_id_ostr << "m_vao_id: ";
            vao_id_ostr << mesh.m_vao_gl_id;
            if (ImGui::TreeNode(vao_id_ostr.str().c_str()))
            {
                std::stringstream m_vertices_ostr;
                m_vertices_ostr << mesh.m_vertices.size();
                ImGui::Text("vertices count: %s", m_vertices_ostr.str().c_str());
                std::stringstream m_indices_ostr;
                m_indices_ostr << mesh.m_indices.size();
                ImGui::Text("indices count: %s", m_indices_ostr.str().c_str());
                if (ImGui::TreeNode("Textures:"))
                {
                    for (const Texture &p_texture_id : mesh.m_textures)
                    {
                        std::stringstream ostr_gl_id;
                        ostr_gl_id << p_texture_id.m_gl_id;
                        ImGui::Text("m_gl_id: %s", ostr_gl_id.str().c_str());

                        std::stringstream ostr_texture_type;
                        ostr_texture_type << p_texture_id.m_type;
                        ImGui::Text("m_type: %s", ostr_texture_type.str().c_str());
// TODO :: Refactor a bunch of this
#if 0
                        const TextureInfo &texture_data = TextureDb::map.at(p_texture_id.m_gl_id);
                        std::stringstream ostr_texture_gl_id;
                        ostr_texture_gl_id << texture_data.m_gl_id;
                        ImGui::Text("id: %s", ostr_texture_gl_id.str().c_str());

                        std::stringstream ostr_texture_path;
                        ostr_texture_path << texture_data.m_path;
                        ImGui::Text("path: %s", ostr_texture_path.str().c_str());

                        std::stringstream ostr_texture_type;
                        ostr_texture_type << texture_data.m_type;
                        ImGui::Text("type: %s", ostr_texture_type.str().c_str());

                        std::stringstream ostr_texture_size;
                        ostr_texture_size << texture_data.m_dimension[0] << " " << texture_data.m_dimension[1] << ", " << texture_data.m_dimension[2];
                        ImGui::Text("dimension: %s", ostr_texture_size.str().c_str());

                        // TODO :: Figure out how to resize the image properly, maintaing its aspect ratio etc etc
                        ImGui::Image(
                            (ImTextureID)(intptr_t)texture_data.m_gl_id,
                            ImVec2(
                                static_cast<float>(texture_data.m_dimension[0]),
                                static_cast<float>(texture_data.m_dimension[1])));
#endif
                    };
                    ImGui::TreePop();
                }
                ImGui::TreePop();
            }
        };
    }
    ImGui::End();
};
