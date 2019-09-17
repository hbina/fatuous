#include "processes/rendering_process.hpp"
#include "akarin_database/shader/shader_database.hpp"
#include "akarin_database/glfw/akarin_glfw.hpp"
#include "akarin_database/lighting/lighting_database.hpp"
#include "akarin_database/model/model_database.hpp"
#include "akarin_database/mesh/mesh_database.hpp"
#include "akarin_database/shader/shader_database.hpp"
#include "components/transform.hpp"
#include "misc/shader_utilities.hpp"
#include "akarin_imgui/lighting_database_window.hpp"
#include "akarin_imgui/akarin_imgui.hpp"
#include "systems/skybox_system.hpp"
#include "systems/akarin_camera_system.hpp"
#include "misc/opengl_settings.hpp"

#include "glad/glad.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/glm.hpp"

#include <array>

void draw(
    const GLuint,
    const Model &,
    const Transform &,
    bool draw_depth = false);

void prepare_shadow(
    entt::registry &) noexcept;

void normal_render(
    entt::registry &,
    const GLuint) noexcept;

void RenderingProcess::render(
    entt::registry &p_reg) noexcept
{
    static bool first = true;
    static GLuint model_shader = 0;
    if (first)
    {
        first = false;
        model_shader = ShaderDb::link_shader_files(
            {ShaderDb::load_shader_file(
                 "./shaders/vertex/model.glsl",
                 ShaderType::VERTEX),
             ShaderDb::load_shader_file(
                 "./shaders/fragment/model.glsl",
                 ShaderType::FRAGMENT)});
        LightingDb::create_dir_light();
        LightingDb::create_point_light();
    }
    OpenGLSettings::update();
    prepare_shadow(p_reg);
    normal_render(p_reg, model_shader);

    SkyboxSystem::render(p_reg);
    AkarinImgui::render(p_reg);
    glFlush();
    AkarinGLFW::swap_buffers();
};

void normal_render(
    entt::registry &p_reg,
    const GLuint model_shader) noexcept
{
    OpenGLSettings::gl_clear();
    ShaderUtilities::use(model_shader);
    ShaderUtilities::configure_lighting(model_shader);
    p_reg.view<Model, Transform>()
        .each([&](
                  const Model &p_model_data,
                  const Transform &p_transform) {
            draw(
                model_shader,
                p_model_data,
                p_transform);
        });
};

void prepare_shadow(
    entt::registry &p_reg) noexcept
{
    for (const std::pair<const std::size_t, PointLight> &iter : LightingDb::point_map)
    {
        const PointLight &point_light = iter.second;
        // Create depth cubemap transformation matrices
        ShaderUtilities::prepare_omni_shadow(point_light);
        p_reg.view<Model, Transform>()
            .each([&](
                      const Model &p_model_data,
                      const Transform &p_transform) {
                draw(
                    point_light.m_buffer.m_shader,
                    p_model_data,
                    p_transform,
                    true);
            });
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        OpenGLSettings::refresh_settings();
    }
};

void draw(
    const GLuint p_shader,
    const Model &p_model,
    const Transform &p_transform,
    const bool draw_depth)
{
    ShaderUtilities::transform_shader(
        p_shader,
        AkarinCameraSystem::get_projection(),
        AkarinCameraSystem::get_view(),
        p_transform.m_position,
        p_transform.m_scale,
        draw_depth);
    for (const std::size_t &mesh : p_model.m_meshes)
        MeshDb::meshes_map.at(mesh).draw(p_shader, draw_depth);
};
