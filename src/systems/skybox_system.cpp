#include "systems/skybox_system.hpp"
#include "systems/akarin_camera_system.hpp"
#include "akarin_database/texture/texture_database.hpp"
#include "akarin_database/shader/shader_database.hpp"
#include "misc/opengl_settings.hpp"
#include "misc/shader_utilities.hpp"

#include "glad/glad.h"
#include "stb/stb_image.h"

#include <array>
#include <iostream>

const std::array<float, 108> skybox_vertices{
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

void SkyboxSystem::render() noexcept
{
    static GLuint shader_id = 0;
    static GLuint vao_id = 0, vbo_id = 0;
    static GLuint texture_id = 0;
    static bool initialized = false;
    if (!initialized)
    {
        initialized = true;
        shader_id = ShaderDb::link_shader_codes(
            {ShaderDb::load_shader_file(
                 "./shaders/vertex/skybox.glsl",
                 ShaderType::VERTEX),
             ShaderDb::load_shader_file(
                 "./shaders/fragment/skybox.glsl",
                 ShaderType::FRAGMENT)});
        texture_id = TextureDb::load_cube_texture(faces);

        glGenVertexArrays(1, &vao_id);
        glGenBuffers(1, &vbo_id);
        glBindVertexArray(vao_id);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
        glBufferData(GL_ARRAY_BUFFER, sizeof(skybox_vertices), skybox_vertices.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    }
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    ShaderUtilities::use(shader_id);
    const glm::mat4 &view = glm::mat4(glm::mat3(AkarinCameraSystem::get_view()));
    ShaderUtilities::setMat4(shader_id, "view", view);
    ShaderUtilities::setMat4(shader_id, "projection", AkarinCameraSystem::get_projection());
    glBindVertexArray(vao_id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    OpenGLSettings::refresh_settings();
};
