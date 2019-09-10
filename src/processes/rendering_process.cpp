#include "processes/rendering_process.hpp"
#include "akarin_database/shader/shader_program_database.hpp"
#include "akarin_database/shader/shader_code_database.hpp"
#include "akarin_database/model/model_database.hpp"
#include "akarin_database/mesh/mesh_database.hpp"
#include "types/shader.hpp"
#include "types/transform.hpp"
#include "misc/shader_utilities.hpp"
#include "akarin_imgui/lighting_database_window.hpp"
#include "akarin_imgui/akarin_imgui.hpp"
#include "systems/skybox_system.hpp"
#include "systems/akarin_camera_system.hpp"
#include "misc/opengl_settings.hpp"
#include "akarin_database/singleton/glfw/akarin_glfw.hpp"

#include "glad/glad.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/glm.hpp"

void draw(
    const GLuint,
    const ModelData &,
    const Transform &);
void add_dirlight(
    const GLuint,
    const bool) noexcept;
void add_pointlight(
    const GLuint,
    const bool) noexcept;
void add_spotlight(
    const GLuint,
    const bool) noexcept;

void RenderingProcess::render(
    entt::registry &p_reg) noexcept
{
    static GLuint p_shader_id = ShaderProgramDatabase::get_instance().link_shader_codes(
        {ShaderCodeDatabase::load_shader_code_file("./shaders/model.vs"),
         ShaderCodeDatabase::load_shader_code_file("./shaders/model.fs")});
    auto entity_view = p_reg.view<ModelData, Transform>();
    OpenGLSettings::gl_clear();
    OpenGLSettings::update();
    ShaderUtilities::use(p_shader_id);
    for (const entt::entity &entity : entity_view)
    {
        // TODO :: This should instead query the database.
        // Lighting stuff
        /**
        add_dirlight(
            p_shader_id,
            LightingDatabaseWindow::enable_directional_light);
        add_pointlight(
            p_shader_id,
            LightingDatabaseWindow::enable_point_light);
        add_spotlight(
            p_shader_id,
            LightingDatabaseWindow::enable_spot_light);
        **/
        // Draw
        draw(
            p_shader_id,
            entity_view.get<ModelData>(entity),
            entity_view.get<Transform>(entity));
    }
    SkyboxSystem::render();
    AkarinImgui::render();
    AkarinGLFW::get_instance().swap_buffers();
};

void draw(
    const GLuint p_shader_program_id,
    const ModelData &p_model,
    const Transform &p_transform)
{
    ShaderUtilities::transform_shader(
        p_shader_program_id,
        AkarinCameraSystem::get_projection(),
        AkarinCameraSystem::get_view(),
        p_transform.position,
        p_transform.scale);
    for (const std::size_t &p_mesh_id : p_model.m_meshes)
    {
        MeshDatabase::meshes_map.at(p_mesh_id).draw(p_shader_program_id);
    }
};

/**
void add_dirlight(
    const GLuint p_shader_id,
    const bool p_enabled) noexcept
{
    ShaderUtilities::setVec3(
        p_shader_id,
        "camera_position",
        AkarinCameraSystem::get_position());
    // TODO :: Shininess is actually part of Directional Light, as such, we need a separate Material helper class
    ShaderUtilities::setFloat(
        p_shader_id,
        "material.shininess",
        LightingDatabaseWindow::directional_light.shininess);
    ShaderUtilities::setVec3(
        p_shader_id,
        "directional_light.direction",
        LightingDatabaseWindow::directional_light.direction);
    ShaderUtilities::setVec3(
        p_shader_id,
        "directional_light.ambient",
        p_enabled ? LightingDatabaseWindow::directional_light.ambient : std::array<float, 3>{0, 0, 0});
    ShaderUtilities::setVec3(
        p_shader_id,
        "directional_light.diffuse",
        p_enabled ? LightingDatabaseWindow::directional_light.diffuse : std::array<float, 3>{0, 0, 0});
    ShaderUtilities::setVec3(
        p_shader_id,
        "directional_light.specular",
        p_enabled ? LightingDatabaseWindow::directional_light.specular : std::array<float, 3>{0, 0, 0});
};

void add_pointlight(
    const GLuint p_shader_id,
    const bool p_enabled) noexcept
{
    ShaderUtilities::setVec3(
        p_shader_id,
        "point_light.position",
        AkarinCameraSystem::get_position());
    ShaderUtilities::setVec3(
        p_shader_id,
        "point_light.ambient",
        p_enabled ? LightingDatabaseWindow::point_light.ambient : std::array<float, 3>{0, 0, 0});
    ShaderUtilities::setVec3(
        p_shader_id,
        "point_light.diffuse",
        p_enabled ? LightingDatabaseWindow::point_light.diffuse : std::array<float, 3>{0, 0, 0});
    ShaderUtilities::setVec3(
        p_shader_id,
        "point_light.specular",
        p_enabled ? LightingDatabaseWindow::point_light.specular : std::array<float, 3>{0, 0, 0});
    ShaderUtilities::setFloat(
        p_shader_id,
        "point_light.constant",
        LightingDatabaseWindow::point_light.constant);
    ShaderUtilities::setFloat(
        p_shader_id,
        "point_light.linear",
        LightingDatabaseWindow::point_light.linear);
    ShaderUtilities::setFloat(
        p_shader_id,
        "point_light.quadratic",
        LightingDatabaseWindow::point_light.quadratic);
};

void add_spotlight(
    const GLuint p_shader_id,
    const bool p_enabled) noexcept
{
    ShaderUtilities::setVec3(
        p_shader_id,
        "spot_light.position",
        AkarinCameraSystem::get_position());
    ShaderUtilities::setVec3(
        p_shader_id,
        "spot_light.direction",
        AkarinCameraSystem::get_front());
    ShaderUtilities::setVec3(
        p_shader_id,
        "spot_light.ambient",
        p_enabled ? LightingDatabaseWindow::spot_light.ambient : std::array<float, 3>{0, 0, 0});
    ShaderUtilities::setVec3(
        p_shader_id,
        "spot_light.diffuse",
        p_enabled ? LightingDatabaseWindow::spot_light.diffuse : std::array<float, 3>{0, 0, 0});
    ShaderUtilities::setVec3(
        p_shader_id,
        "spot_light.specular",
        p_enabled ? LightingDatabaseWindow::spot_light.specular : std::array<float, 3>{0, 0, 0});
    ShaderUtilities::setFloat(
        p_shader_id,
        "spot_light.constant",
        1.0f);
    ShaderUtilities::setFloat(
        p_shader_id,
        "spot_light.linear",
        0.09f);
    ShaderUtilities::setFloat(
        p_shader_id,
        "spot_light.quadratic",
        0.032f);
    ShaderUtilities::setFloat(
        p_shader_id,
        "spot_light.cutOff",
        glm::cos(glm::radians(LightingDatabaseWindow::spot_light.cutOff)));
    ShaderUtilities::setFloat(
        p_shader_id,
        "spot_light.outerCutOff",
        glm::cos(glm::radians(LightingDatabaseWindow::spot_light.outerCutOff)));
};
*/
