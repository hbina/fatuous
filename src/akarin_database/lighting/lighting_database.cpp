#include "akarin_database/lighting/lighting_database.hpp"
#include "akarin_imgui/lighting_database_window.hpp"
#include "misc/shader_utilities.hpp"
#include "systems/akarin_camera_system.hpp"

std::size_t directional_light_counter = 1;
std::size_t point_light_counter = 1;
std::size_t spot_light_counter = 1;

std::unordered_map<std::size_t, DirectionalLight> LightingDb::dir_map;
std::unordered_map<std::size_t, PointLight> LightingDb::point_map;
std::unordered_map<std::size_t, SpotLight> LightingDb::spot_map;

void LightingDb::prepare_normal_render(
    const GLuint p_shader_id) noexcept {
    // TODO :: Prepare for lighting stuff...
};

void LightingDb::create_dir_light() noexcept
{
    dir_map.emplace(
        std::make_pair(
            directional_light_counter++,
            DirectionalLight(22.0f,
                             glm::vec3(0.0f, 1.0f, 0.0f),
                             PhongLight(
                                 glm::vec3(0.7f),
                                 glm::vec3(0.7f),
                                 glm::vec3(0.7f)))));
};

void LightingDb::create_point_light() noexcept
{
    point_map.emplace(
        std::make_pair(
            point_light_counter++,
            PointLight(
                glm::vec3(0.0f),
                Intensity(255.0f, 255.0f, 255.0f, 255.0f),
                PhongLight(
                    glm::vec3(255.0f),
                    glm::vec3(255.0f),
                    glm::vec3(255.0f)),
                DepthBuffer(glm::vec2(500.0f)))));
    // TODO :: Since this is a one time thing... need to pass as parameter...
};

void LightingDb::create_spot_light() noexcept
{
    spot_map.emplace(
        std::make_pair(
            spot_light_counter++,
            SpotLight(
                glm::vec3(0.0f),
                glm::vec3(0.0f),
                0.0f, 0.0f,
                Intensity(255.0f, 255.0f, 255.0f, 255.0f),
                PhongLight(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f)))));
};
