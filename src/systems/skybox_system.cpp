#include "systems/skybox_system.hpp"
#include "systems/akarin_camera_system.hpp"
#include "akarin_database/texture/texture_database.hpp"
#include "akarin_database/shader/shader_code_database.hpp"
#include "akarin_database/shader/shader_program_database.hpp"
#include "misc/opengl_settings.hpp"
#include "misc/shader_utilities.hpp"

#include "glad/glad.h"
#include "stb/stb_image.h"

#include <array>
#include <iostream>

const std::array<float, 108> g_skybox_vertices{
    // positions
    -1.0f, 1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,

    -1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,

    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,

    -1.0f, 1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, 1.0f};

const std::array<std::string, 6> faces{
    "./resources/skybox/right.jpg",
    "./resources/skybox/left.jpg",
    "./resources/skybox/top.jpg",
    "./resources/skybox/bottom.jpg",
    "./resources/skybox/front.jpg",
    "./resources/skybox/back.jpg"};

GLuint g_skybox_shader_id = 0;
GLuint g_skybox_vao_id = 0, g_skybox_vbo_id = 0;
Texture g_skybox_texture_id = 0;

// SkyBox should not be affected by OpenGLSettings
void init_skybox_vertices() noexcept;

void SkyboxSystem::render() noexcept
{
    static bool initialized = false;
    if (!initialized)
    {
        g_skybox_shader_id = ShaderProgramDb::link_shader_codes(
            {ShaderCodeDatabase::load_shader_file(
                 "./shaders/vertex/skybox.glsl",
                 ShaderType::VERTEX),
             ShaderCodeDatabase::load_shader_file(
                 "./shaders/fragment/skybox.glsl",
                 ShaderType::FRAGMENT)});
        g_skybox_texture_id = TextureDatabase::load_cube_texture(faces);

        init_skybox_vertices();
        initialized = true;
    }
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    ShaderUtilities::use(g_skybox_shader_id);
    const glm::mat4 &view = glm::mat4(glm::mat3(AkarinCameraSystem::get_view()));
    ShaderUtilities::setMat4(g_skybox_shader_id, "view", view);
    ShaderUtilities::setMat4(g_skybox_shader_id, "projection", AkarinCameraSystem::get_projection());
    glBindVertexArray(g_skybox_vao_id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, TextureDatabase::textures_map[g_skybox_texture_id.m_id].m_gl_id);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    OpenGLSettings::update_depth_function();
    OpenGLSettings::update_cull_face();
};

void init_skybox_vertices() noexcept
{
    glGenVertexArrays(1, &g_skybox_vao_id);
    glGenBuffers(1, &g_skybox_vbo_id);
    glBindVertexArray(g_skybox_vao_id);
    glBindBuffer(GL_ARRAY_BUFFER, g_skybox_vbo_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_skybox_vertices), g_skybox_vertices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
};
