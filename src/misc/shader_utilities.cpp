#include "misc/shader_utilities.hpp"
#include "akarin_imgui/lighting_database_window.hpp"
#include "systems/akarin_camera_system.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/glm.hpp"

void ShaderUtilities::use(
    const GLuint p_shader_program_id) noexcept
{
    glUseProgram(p_shader_program_id);
};

void ShaderUtilities::transform_shader(
    const GLuint shader_id,
    const glm::mat4 &p_projection,
    const glm::mat4 &p_view,
    const glm::vec3 &p_position,
    const glm::vec3 &p_scale,
    const bool draw_depth) noexcept

{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, p_position);
    model = glm::scale(model, p_scale);
    // TODO :: Add rotation to Transform
    ShaderUtilities::setMat4(shader_id, "model", model);
    if (!draw_depth)
        ShaderUtilities::setMat4(shader_id, "projection_view_model", p_projection * p_view * model);
};

void ShaderUtilities::setBool(
    const GLuint p_shader_program_id,
    const std::string &p_property_name,
    const bool p_value) noexcept
{
    glUniform1i(glGetUniformLocation(p_shader_program_id, p_property_name.c_str()), (int)p_value);
};

void ShaderUtilities::setInt(
    const GLuint p_shader_program_id,
    const std::string &p_property_name,
    const int p_value) noexcept
{
    glUniform1i(glGetUniformLocation(p_shader_program_id, p_property_name.c_str()), p_value);
};

void ShaderUtilities::setFloat(
    const GLuint p_shader_program_id,
    const std::string &p_property_name,
    const float p_value) noexcept
{
    glUniform1f(glGetUniformLocation(p_shader_program_id, p_property_name.c_str()), p_value);
};

void ShaderUtilities::setVec2(
    const GLuint p_shader_program_id,
    const std::string &p_property_name,
    const glm::vec2 &p_value) noexcept
{
    glUniform2fv(glGetUniformLocation(p_shader_program_id, p_property_name.c_str()), 1, &p_value[0]);
};

void ShaderUtilities::setVec2(
    const GLuint p_shader_program_id,
    const std::string &p_property_name,
    const std::array<float, 2> &p_array) noexcept
{
    glUniform2f(glGetUniformLocation(p_shader_program_id, p_property_name.c_str()), p_array[0], p_array[1]);
};

void ShaderUtilities::setVec3(
    const GLuint p_shader_program_id,
    const std::string &p_property_name,
    const glm::vec3 &p_value) noexcept
{
    glUniform3fv(glGetUniformLocation(p_shader_program_id, p_property_name.c_str()), 1, &p_value[0]);
};

void ShaderUtilities::setVec3(
    const GLuint p_shader_program_id,
    const std::string &p_property_name,
    const std::array<float, 3> &p_array) noexcept
{
    glUniform3f(glGetUniformLocation(p_shader_program_id, p_property_name.c_str()), p_array[0], p_array[1], p_array[2]);
};

void ShaderUtilities::setVec4(
    const GLuint p_shader_program_id,
    const std::string &p_property_name,
    const glm::vec4 &p_value) noexcept
{
    glUniform4fv(glGetUniformLocation(p_shader_program_id, p_property_name.c_str()), 1, &p_value[0]);
};

void ShaderUtilities::setVec4(
    const GLuint p_shader_program_id,
    const std::string &p_property_name,
    const std::array<float, 4> &p_array) noexcept
{
    glUniform4f(glGetUniformLocation(p_shader_program_id, p_property_name.c_str()), p_array[0], p_array[1], p_array[2], p_array[3]);
};

void ShaderUtilities::setMat2(
    const GLuint p_shader_program_id,
    const std::string &p_property_name,
    const glm::mat2 &p_value) noexcept
{
    glUniformMatrix2fv(glGetUniformLocation(p_shader_program_id, p_property_name.c_str()), 1, GL_FALSE, &p_value[0][0]);
};

void ShaderUtilities::setMat3(
    const GLuint p_shader_program_id,
    const std::string &p_property_name,
    const glm::mat3 &p_value) noexcept
{
    glUniformMatrix3fv(glGetUniformLocation(p_shader_program_id, p_property_name.c_str()), 1, GL_FALSE, &p_value[0][0]);
};

void ShaderUtilities::setMat4(
    const GLuint p_shader_program_id,
    const std::string &p_property_name,
    const glm::mat4 &p_value) noexcept
{
    glUniformMatrix4fv(glGetUniformLocation(p_shader_program_id, p_property_name.c_str()), 1, GL_FALSE, &p_value[0][0]);
};

void ShaderUtilities::attach_dir_light(
    const GLuint p_shader_id,
    const DirectionalLight &directional_light) noexcept
{
    // TODO :: Shininess is actually part of Directional Light, as such, we need a separate Material helper class
    setFloat(
        p_shader_id,
        "material.shininess",
        directional_light.m_shininess);
    setVec3(
        p_shader_id,
        "directional_light.direction",
        directional_light.m_direction);
    setVec3(
        p_shader_id,
        "directional_light.ambient",
        LightingDbWindow::enable_dir_light ? directional_light.m_phong.m_ambient
                                           : glm::vec3(0.0f));
    setVec3(
        p_shader_id,
        "directional_light.diffuse",
        LightingDbWindow::enable_dir_light ? directional_light.m_phong.m_diffuse
                                           : glm::vec3(0.0f));
    setVec3(
        p_shader_id,
        "directional_light.specular",
        LightingDbWindow::enable_dir_light ? directional_light.m_phong.m_specular
                                           : glm::vec3(0.0f));
};

void ShaderUtilities::attach_point_light(
    const GLuint p_shader_id,
    const PointLight &point_light) noexcept
{
    setVec3(
        p_shader_id,
        "point_light.position",
        point_light.m_position);
    setVec3(
        p_shader_id,
        "point_light.ambient",
        LightingDbWindow::enable_point_light ? point_light.m_phong.m_ambient
                                             : glm::vec3(0.0f));
    setVec3(
        p_shader_id,
        "point_light.diffuse",
        LightingDbWindow::enable_point_light ? point_light.m_phong.m_diffuse
                                             : glm::vec3(0.0f));
    setVec3(
        p_shader_id,
        "point_light.specular",
        LightingDbWindow::enable_point_light ? point_light.m_phong.m_specular
                                             : glm::vec3(0.0f));
    setFloat(
        p_shader_id,
        "point_light.attenuation_value",
        point_light.m_intensity.m_attval);
    setFloat(
        p_shader_id,
        "point_light.constant",
        point_light.m_intensity.m_constant);
    setFloat(
        p_shader_id,
        "point_light.linear",
        point_light.m_intensity.m_linear);
    setFloat(
        p_shader_id,
        "point_light.quadratic",
        point_light.m_intensity.m_quadratic);
    ShaderUtilities::setInt(
        p_shader_id,
        "depth_map",
        4);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_CUBE_MAP, point_light.m_buffer.m_cube_map);
};

void ShaderUtilities::add_spot_light(
    const GLuint p_shader_id,
    const bool p_enabled) noexcept
{
    setVec3(
        p_shader_id,
        "spot_light.position",
        AkarinCameraSystem::get_position());
    setVec3(
        p_shader_id,
        "spot_light.direction",
        AkarinCameraSystem::get_front());
    setVec3(
        p_shader_id,
        "spot_light.ambient",
        p_enabled ? LightingDbWindow::spot_light.ambient : std::array<float, 3>{0, 0, 0});
    setVec3(
        p_shader_id,
        "spot_light.diffuse",
        p_enabled ? LightingDbWindow::spot_light.diffuse : std::array<float, 3>{0, 0, 0});
    setVec3(
        p_shader_id,
        "spot_light.specular",
        p_enabled ? LightingDbWindow::spot_light.specular : std::array<float, 3>{0, 0, 0});
    setFloat(
        p_shader_id,
        "point_light.attenuation_value",
        LightingDbWindow::spot_light.attenuation_value);
    setFloat(
        p_shader_id,
        "spot_light.constant",
        1.0f);
    setFloat(
        p_shader_id,
        "spot_light.linear",
        0.09f);
    setFloat(
        p_shader_id,
        "spot_light.quadratic",
        0.032f);
    setFloat(
        p_shader_id,
        "spot_light.cutOff",
        glm::cos(glm::radians(LightingDbWindow::spot_light.cutOff)));
    setFloat(
        p_shader_id,
        "spot_light.outerCutOff",
        glm::cos(glm::radians(LightingDbWindow::spot_light.outerCutOff)));
};
