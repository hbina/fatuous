#include "akarin_database/lighting/lighting_database.hpp"
#include "akarin_imgui/lighting_database_window.hpp"
#include "misc/shader_utilities.hpp"
#include "systems/akarin_camera_system.hpp"

std::unordered_map<std::size_t, DirectionalLight> LightingDb::dir_map;
std::unordered_map<std::size_t, PointLight> LightingDb::point_map;
std::unordered_map<std::size_t, SpotLight> LightingDb::spot_map;

void add_dirlight(
    const GLuint,
    const bool) noexcept;
void add_pointlight(
    const GLuint,
    const bool) noexcept;
void add_spotlight(
    const GLuint,
    const bool) noexcept;

void LightingDb::prepare_light(
    const GLuint p_shader_id) noexcept
{
    add_dirlight(
        p_shader_id,
        LightingDbWindow::enable_directional_light);
    add_pointlight(
        p_shader_id,
        LightingDbWindow::enable_point_light);
    add_spotlight(
        p_shader_id,
        LightingDbWindow::enable_spot_light);
};

void add_dirlight(
    const GLuint p_shader_id,
    const bool p_enabled) noexcept
{
    // TODO :: Shininess is actually part of Directional Light, as such, we need a separate Material helper class
    ShaderUtilities::setFloat(
        p_shader_id,
        "material.shininess",
        LightingDbWindow::directional_light.m_shininess);
    ShaderUtilities::setVec3(
        p_shader_id,
        "directional_light.direction",
        LightingDbWindow::directional_light.m_direction);
    ShaderUtilities::setVec3(
        p_shader_id,
        "directional_light.ambient",
        p_enabled ? LightingDbWindow::directional_light.m_phong.m_ambient : std::array<float, 3>{0, 0, 0});
    ShaderUtilities::setVec3(
        p_shader_id,
        "directional_light.diffuse",
        p_enabled ? LightingDbWindow::directional_light.m_phong.m_diffuse : std::array<float, 3>{0, 0, 0});
    ShaderUtilities::setVec3(
        p_shader_id,
        "directional_light.specular",
        p_enabled ? LightingDbWindow::directional_light.m_phong.m_specular : std::array<float, 3>{0, 0, 0});
};

void add_pointlight(
    const GLuint p_shader_id,
    const bool p_enabled) noexcept
{
    ShaderUtilities::setVec3(
        p_shader_id,
        "point_light.position",
        LightingDbWindow::point_light.m_position);
    ShaderUtilities::setVec3(
        p_shader_id,
        "point_light.ambient",
        p_enabled ? LightingDbWindow::point_light.m_phong.m_ambient
                  : std::array<float, 3>{0, 0, 0});
    ShaderUtilities::setVec3(
        p_shader_id,
        "point_light.diffuse",
        p_enabled ? LightingDbWindow::point_light.m_phong.m_diffuse
                  : std::array<float, 3>{0, 0, 0});
    ShaderUtilities::setVec3(
        p_shader_id,
        "point_light.specular",
        p_enabled ? LightingDbWindow::point_light.m_phong.m_specular
                  : std::array<float, 3>{0, 0, 0});
    ShaderUtilities::setFloat(
        p_shader_id,
        "point_light.attenuation_value",
        LightingDbWindow::point_light.m_intensity.m_attval);
    ShaderUtilities::setFloat(
        p_shader_id,
        "point_light.constant",
        LightingDbWindow::point_light.m_intensity.m_constant);
    ShaderUtilities::setFloat(
        p_shader_id,
        "point_light.linear",
        LightingDbWindow::point_light.m_intensity.m_linear);
    ShaderUtilities::setFloat(
        p_shader_id,
        "point_light.quadratic",
        LightingDbWindow::point_light.m_intensity.m_quadratic);
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
        p_enabled ? LightingDbWindow::spot_light.ambient : std::array<float, 3>{0, 0, 0});
    ShaderUtilities::setVec3(
        p_shader_id,
        "spot_light.diffuse",
        p_enabled ? LightingDbWindow::spot_light.diffuse : std::array<float, 3>{0, 0, 0});
    ShaderUtilities::setVec3(
        p_shader_id,
        "spot_light.specular",
        p_enabled ? LightingDbWindow::spot_light.specular : std::array<float, 3>{0, 0, 0});
    ShaderUtilities::setFloat(
        p_shader_id,
        "point_light.attenuation_value",
        LightingDbWindow::spot_light.attenuation_value);
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
        glm::cos(glm::radians(LightingDbWindow::spot_light.cutOff)));
    ShaderUtilities::setFloat(
        p_shader_id,
        "spot_light.outerCutOff",
        glm::cos(glm::radians(LightingDbWindow::spot_light.outerCutOff)));
};

void LightingDb::create_dir_light() noexcept
{
    // std::array<float, 3> ambient = {0.1f, 0.1f, 0.1f};
    // std::array<float, 3> diffuse = {1.0f, 1.0f, 1.0f};
    // std::array<float, 3> specular = {0.1f, 0.1f, 0.1f};
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
