#include "akarin_database/lighting/lighting_database.hpp"
#include "akarin_imgui/lighting_database_window.hpp" // Circular dependency...remove this...
#include "akarin_database/shader/shader_database.hpp"
#include "misc/shader_utilities.hpp"
#include "systems/akarin_camera_system.hpp"

std::unordered_map<std::size_t, DirectionalLight> LightingDb::dir_map;
std::unordered_map<std::size_t, PointLight> LightingDb::point_map;
std::unordered_map<std::size_t, SpotLight> LightingDb::spot_map;

void LightingDb::prepare_light(
    const GLuint p_shader_id) noexcept
{
    static bool first = true;
    if (first)
    {
        first = false;
        create_dir_light();
        create_point_light(256, 256);
    }
    for (const auto &dir_light : dir_map)
    {
        ShaderUtilities::attach_dir_light(
            p_shader_id,
            dir_light.second);
    };
    for (const auto &point_light : point_map)
    {
        ShaderUtilities::attach_point_light(
            p_shader_id,
            point_light.second);
    }
    ShaderUtilities::add_spot_light(
        p_shader_id,
        LightingDbWindow::enable_spot_light);

    // TODO :: Move this to PointLight
    ShaderUtilities::setFloat(
        p_shader_id,
        "far_plane",
        LightingDbWindow::far_plane);
    ShaderUtilities::setFloat(
        p_shader_id,
        "shadow_bias",
        LightingDbWindow::shadow_bias);
    ShaderUtilities::setBool(
        p_shader_id,
        "enable_shadow",
        LightingDbWindow::enable_shadow);
    ShaderUtilities::setBool(
        p_shader_id,
        "enable_shadow_debug",
        LightingDbWindow::enable_shadow_debug);
    ShaderUtilities::setVec3(
        p_shader_id,
        "camera_position",
        AkarinCameraSystem::get_position());
};

void LightingDb::create_dir_light() noexcept
{
    static std::size_t directional_light_counter = 1;
    dir_map.emplace(
        std::make_pair(
            directional_light_counter++,
            DirectionalLight(
                {1.0f, 1.0f, 1.0f},
                PhongLight(
                    {0.1f, 0.1f, 0.1f},
                    {1.0f, 1.0f, 1.0f},
                    {0.1f, 0.1f, 0.1f}))));
};

void LightingDb::create_point_light(
    const GLsizei p_width,
    const GLsizei p_height) noexcept
{
    static std::size_t point_light_counter = 1;
    std::size_t light_id = point_light_counter++;

    GLuint light_shader = 0u;
    GLuint light_fbo = 0u;
    GLuint light_cube_map = 0u;
    light_shader = ShaderDb::link_shader_files(
        {ShaderDb::load_shader_file(
             "./shaders/vertex/omnishadow.glsl",
             ShaderType::VERTEX),
         ShaderDb::load_shader_file(
             "./shaders/fragment/omnishadow.glsl",
             ShaderType::FRAGMENT),
         ShaderDb::load_shader_file(
             "./shaders/geometry/omnishadow.glsl",
             ShaderType::GEOMETRY)});

    // generate the cubemap
    glGenFramebuffers(1, &light_fbo);
    glGenTextures(1, &light_cube_map);

    // generate the single cubemap faces as 2d depth-valued texture images
    glBindTexture(GL_TEXTURE_CUBE_MAP, light_cube_map);
    for (unsigned int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT,
                     p_width,
                     p_height,
                     0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    }
    // Set the texture parameters
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // Pass the cubemap as the depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, light_fbo);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, light_cube_map, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    point_map.emplace(
        std::make_pair(
            light_id,
            PointLight(
                {0.0f, 0.0f, 0.0f},
                Intensity(
                    25.0f,
                    0.5f, 0.01f, 0.03f),
                PhongLight(
                    {1.0f, 1.0f, 1.0f},
                    {1.0f, 1.0f, 1.0f},
                    {1.0f, 1.0f, 1.0f}),
                DepthBuffer(p_width, p_height, light_cube_map, light_fbo, light_shader))));
};
