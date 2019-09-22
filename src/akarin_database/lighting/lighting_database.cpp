#include "akarin_database/lighting/lighting_database.hpp"
#include "akarin_imgui/lighting_database_window.hpp" // Circular dependency...remove this...
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
        create_point_light();
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

void LightingDb::create_point_light() noexcept
{
    static std::size_t point_light_counter = 1;
    point_map.emplace(
        std::make_pair(
            point_light_counter++,
            PointLight(
                {0.0f, 0.0f, 0.0f},
                Intensity(
                    25.0f,
                    0.5f, 0.01f, 0.03f),
                PhongLight(
                    {1.0f, 1.0f, 1.0f},
                    {1.0f, 1.0f, 1.0f},
                    {1.0f, 1.0f, 1.0f}),
                DepthBuffer(500, 500))));
};
