#include "processes/rendering_process.hpp"
#include "akarin_database/shader/shader_program_database.hpp"
#include "akarin_database/shader/shader_code_database.hpp"
#include "akarin_database/singleton/glfw/akarin_glfw.hpp"
#include "akarin_database/lighting/lighting_database.hpp"
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

#include "glad/glad.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/glm.hpp"

void draw(
    const GLuint,
    const ModelData &,
    const Transform &,
    bool draw_depth = false);

void prepare_shadow(
    entt::registry &p_reg) noexcept;

void render_normal(
    entt::registry &p_reg) noexcept;

void render_cube() noexcept;

glm::vec3 lightPos;
float near_plane = 1.0f;
float far_plane = 25.0f;
GLuint depth_cube_map = 0;
constexpr unsigned int SHADOW_WIDTH = 500, SHADOW_HEIGHT = 500;

void RenderingProcess::render(
    entt::registry &p_reg) noexcept
{
    OpenGLSettings::update();
    lightPos = glm::vec3(
        LightingDatabaseWindow::point_light.position[0],
        LightingDatabaseWindow::point_light.position[1],
        LightingDatabaseWindow::point_light.position[2]);
    prepare_shadow(p_reg);
    render_normal(p_reg);

    SkyboxSystem::render();
    AkarinImgui::render();
    AkarinGLFW::get_instance().swap_buffers();
};

void draw(
    const GLuint p_shader_id,
    const ModelData &p_model,
    const Transform &p_transform,
    const bool draw_depth)
{
    ShaderUtilities::setVec3(
        p_shader_id,
        "camera_position",
        AkarinCameraSystem::get_position());
    ShaderUtilities::transform_shader(
        p_shader_id,
        AkarinCameraSystem::get_projection(),
        AkarinCameraSystem::get_view(),
        p_transform.position,
        p_transform.scale,
        draw_depth);
    for (const std::size_t &p_mesh_id : p_model.m_meshes)
    {
        MeshDatabase::meshes_map.at(p_mesh_id).draw(
            p_shader_id,
            draw_depth);
    }
};

void render_normal(
    entt::registry &p_reg) noexcept
{
    static GLuint model_shader = 0;
    static bool init = false;
    if (!init)
    {
        init = true;
        model_shader = ShaderProgramDb::get_instance().link_shader_codes(
            {ShaderCodeDatabase::load_shader_file(
                 "./shaders/vertex/model.glsl",
                 ShaderType::VERTEX),
             ShaderCodeDatabase::load_shader_file(
                 "./shaders/fragment/model.glsl",
                 ShaderType::FRAGMENT)});
    }
    ShaderUtilities::use(model_shader);
    LightingDb::prepare_light(model_shader);
    OpenGLSettings::gl_clear();
    ShaderUtilities::setInt(model_shader, "depth_map", 4);
    ShaderUtilities::setFloat(model_shader, "far_plane", far_plane);
    ShaderUtilities::setVec3(model_shader, "light_pos", lightPos);
    auto entity_view = p_reg.view<ModelData, Transform>();
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_CUBE_MAP, depth_cube_map);
    for (const entt::entity &entity : entity_view)
    {
        draw(
            model_shader,
            entity_view.get<ModelData>(entity),
            entity_view.get<Transform>(entity));
    }
};

void prepare_shadow(
    entt::registry &p_reg) noexcept
{
    static GLuint depth_map_fbo = 0;
    static GLuint depth_shader = 0;
    static bool init = false;
    if (!init)
    {
        init = true;

        depth_shader = ShaderProgramDb::get_instance().link_shader_codes(
            {ShaderCodeDatabase::load_shader_file(
                 "./shaders/vertex/omnishadow.glsl",
                 ShaderType::VERTEX),
             ShaderCodeDatabase::load_shader_file(
                 "./shaders/fragment/omnishadow.glsl",
                 ShaderType::FRAGMENT),
             ShaderCodeDatabase::load_shader_file(
                 "./shaders/geometry/omnishadow.glsl",
                 ShaderType::GEOMETRY)});

        // generate the cubemap
        glGenFramebuffers(1, &depth_map_fbo);
        glGenTextures(1, &depth_cube_map);

        // generate the single cubemap faces as 2d depth-valued texture images
        glBindTexture(GL_TEXTURE_CUBE_MAP, depth_cube_map);
        for (unsigned int i = 0; i < 6; ++i)
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT,
                         SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

        // Set the texture parameters
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        // Pass the cubemap as the depth buffer
        glBindFramebuffer(GL_FRAMEBUFFER, depth_map_fbo);
        glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depth_cube_map, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    // Create depth cubemap transformation matrices
    glm::mat4 shadow_projection = glm::perspective(glm::radians(90.0f), (float)SHADOW_WIDTH / (float)SHADOW_HEIGHT, near_plane, far_plane);
    std::vector<glm::mat4> shadow_transforms;
    shadow_transforms.push_back(shadow_projection * glm::lookAt(lightPos, lightPos + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    shadow_transforms.push_back(shadow_projection * glm::lookAt(lightPos, lightPos + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    shadow_transforms.push_back(shadow_projection * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
    shadow_transforms.push_back(shadow_projection * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
    shadow_transforms.push_back(shadow_projection * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    shadow_transforms.push_back(shadow_projection * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));

    // Render scene to depth cubemap
    OpenGLSettings::gl_clear();
    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, depth_map_fbo);
    ShaderUtilities::use(depth_shader);
    for (unsigned int i = 0; i < 6; ++i)
        ShaderUtilities::setMat4(depth_shader, "shadowMatrices[" + std::to_string(i) + "]", shadow_transforms[i]);
    ShaderUtilities::setFloat(depth_shader, "far_plane", far_plane);
    ShaderUtilities::setVec3(depth_shader, "light_pos", lightPos);
    auto entity_view = p_reg.view<ModelData, Transform>();
    for (const entt::entity &entity : entity_view)
    {
        draw(
            depth_shader,
            entity_view.get<ModelData>(entity),
            entity_view.get<Transform>(entity),
            true);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
};
