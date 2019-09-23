#include "processes/rendering_process.hpp"
#include "akarin_database/shader/shader_database.hpp"
#include "akarin_database/glfw/akarin_glfw.hpp"
#include "akarin_database/lighting/lighting_database.hpp"
#include "akarin_database/model/model_database.hpp"
#include "akarin_database/mesh/mesh_database.hpp"
#include "components/transform.hpp"
#include "misc/shader_utilities.hpp"
#include "akarin_imgui/lighting_database_window.hpp"
#include "akarin_imgui/akarin_imgui.hpp"
#include "systems/skybox_system.hpp"
#include "systems/akarin_camera_system.hpp"
#include "misc/opengl_settings.hpp"
#include "akarin_database/shader/shader_database.hpp"

#include "glad/glad.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/glm.hpp"

void draw(
    const GLuint,
    const Model &,
    const Transform &,
    bool p_draw_depth = false);

void prepare_shadow(
    entt::registry &) noexcept;

void render_normal(
    entt::registry &) noexcept;

void RenderingProcess::render(
    entt::registry &p_reg) noexcept
{
    OpenGLSettings::update();
    prepare_shadow(p_reg);
    render_normal(p_reg);

    SkyboxSystem::render(p_reg);
    AkarinImgui::render(p_reg);
    AkarinGLFW::swap_buffers();
};

void draw(
    const GLuint p_shader_id,
    const Model &p_model,
    const Transform &p_transform,
    const bool p_draw_depth)
{
    ShaderUtilities::transform_shader(
        p_shader_id,
        AkarinCameraSystem::get_projection(),
        AkarinCameraSystem::get_view(),
        p_transform.m_position,
        p_transform.m_scale,
        p_draw_depth);
    for (const Mesh &mesh : p_model.m_meshes)
        mesh.draw(p_shader_id, p_draw_depth);
};

void render_normal(
    entt::registry &p_reg) noexcept
{
    static GLuint model_shader = 0;
    static bool init = false;
    if (!init)
    {
        init = true;
        model_shader = ShaderDb::link_shader_files(
            {ShaderDb::load_shader_file(
                 "./shaders/vertex/model.glsl",
                 ShaderType::VERTEX),
             ShaderDb::load_shader_file(
                 "./shaders/fragment/model.glsl",
                 ShaderType::FRAGMENT)});
    }
    OpenGLSettings::gl_clear();
    ShaderUtilities::use(model_shader);
    LightingDb::prepare_light(model_shader);
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
    for (const auto &iter : LightingDb::point_map)
    {
        // Create depth cubemap transformation matrices
        glm::mat4 shadow_projection = glm::perspective(
            glm::radians(90.0f),
            static_cast<float>(iter.second.m_buffer.m_width) / static_cast<float>(iter.second.m_buffer.m_height),
            LightingDbWindow::near_plane,
            LightingDbWindow::far_plane);
        std::array<glm::mat4, 6> shadow_transforms = {
            shadow_projection * glm::lookAt(iter.second.m_position, iter.second.m_position + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
            shadow_projection * glm::lookAt(iter.second.m_position, iter.second.m_position + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
            shadow_projection * glm::lookAt(iter.second.m_position, iter.second.m_position + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
            shadow_projection * glm::lookAt(iter.second.m_position, iter.second.m_position + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)),
            shadow_projection * glm::lookAt(iter.second.m_position, iter.second.m_position + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
            shadow_projection * glm::lookAt(iter.second.m_position, iter.second.m_position + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f))};

        // Render scene to depth cubemap
        glViewport(0, 0, iter.second.m_buffer.m_width, iter.second.m_buffer.m_height);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        glBindFramebuffer(GL_FRAMEBUFFER, iter.second.m_buffer.m_fbo);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ShaderUtilities::use(iter.second.m_buffer.m_shader);
        for (unsigned int i = 0; i < 6; ++i)
            ShaderUtilities::setMat4(
                iter.second.m_buffer.m_shader,
                "shadow_matrices[" + std::to_string(i) + "]",
                shadow_transforms[i]);
        ShaderUtilities::setVec3(
            iter.second.m_buffer.m_shader,
            "light_pos",
            iter.second.m_position);
        ShaderUtilities::setFloat(
            iter.second.m_buffer.m_shader,
            "far_plane",
            LightingDbWindow::far_plane);
        p_reg.view<Model, Transform>()
            .each([&](
                      const Model &p_model_data,
                      const Transform &p_transform) {
                draw(
                    iter.second.m_buffer.m_shader,
                    p_model_data,
                    p_transform,
                    true);
            });
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        OpenGLSettings::refresh_settings();
    }
};
