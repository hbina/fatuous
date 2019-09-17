#include "misc/shader_utilities.hpp"
#include "systems/akarin_camera_system.hpp"
#include "akarin_imgui/lighting_database_window.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/glm.hpp"

// TODO :: Consider putting this into akarin_database/

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

void ShaderUtilities::attach_dir_light(
    const GLuint p_id,
    const DirectionalLight &p_light) noexcept
{
    // TODO :: Shininess is actually part of Directional Light, as such, we need a separate Material helper class
    setFloat(p_id,
             "material.shininess",
             p_light.m_shininess);
    setVec3(p_id,
            "directional_light.direction",
            p_light.m_direction);
    setVec3(p_id,
            "directional_light.ambient",
            p_light.m_phong.m_ambient);
    setVec3(p_id,
            "directional_light.diffuse",
            p_light.m_phong.m_diffuse);
    setVec3(p_id,
            "directional_light.specular",
            p_light.m_phong.m_specular);
};

void ShaderUtilities::attach_point_light(
    const GLuint p_id,
    const PointLight &p_light) noexcept
{
    setVec3(p_id,
            "point_light.position",
            p_light.m_pos);
    setVec3(p_id,
            "point_light.ambient",
            p_light.m_phong.m_ambient);
    setVec3(p_id,
            "point_light.diffuse",
            p_light.m_phong.m_diffuse);
    setVec3(p_id,
            "point_light.specular",
            p_light.m_phong.m_specular);
    setFloat(p_id,
             "point_light.attenuation_value",
             p_light.m_intensity.m_attval);
    setFloat(p_id,
             "point_light.constant",
             p_light.m_intensity.m_const);
    setFloat(p_id,
             "point_light.linear",
             p_light.m_intensity.m_linear);
    setFloat(p_id,
             "point_light.quadratic",
             p_light.m_intensity.m_quadr);
    setInt(p_id,
           "depth_map",
           5);
    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_CUBE_MAP, p_light.m_buffer.m_cube_map);
};

void ShaderUtilities::attach_spot_light(
    const GLuint p_id,
    const SpotLight &p_light) noexcept
{
    setVec3(p_id,
            "spot_light.position",
            p_light.m_pos);
    setVec3(p_id,
            "spot_light.direction",
            p_light.m_direction);
    setVec3(p_id,
            "spot_light.ambient",
            p_light.m_phong.m_ambient);
    setVec3(p_id,
            "spot_light.diffuse",
            p_light.m_phong.m_diffuse);
    setVec3(p_id,
            "spot_light.specular",
            p_light.m_phong.m_specular);
    setFloat(p_id,
             "point_light.attenuation_value",
             p_light.m_intensity.m_attval);
    setFloat(p_id,
             "spot_light.constant",
             p_light.m_intensity.m_const);
    setFloat(p_id,
             "spot_light.linear",
             p_light.m_intensity.m_linear);
    setFloat(p_id,
             "spot_light.quadratic",
             p_light.m_intensity.m_quadr);
    setFloat(p_id,
             "spot_light.cutOff",
             glm::cos(glm::radians(p_light.cutOff)));
    setFloat(p_id,
             "spot_light.outerCutOff",
             glm::cos(glm::radians(p_light.outerCutOff)));
};

void ShaderUtilities::prepare_omni_shadow(
    const PointLight &point_light) noexcept
{
    glm::mat4 shadow_projection = glm::perspective(
        glm::radians(90.0f),
        static_cast<float>(point_light.m_buffer.m_dimension.x) /
            static_cast<float>(point_light.m_buffer.m_dimension.y),
        point_light.m_buffer.m_near,
        point_light.m_buffer.m_far);
    const std::array<glm::mat4, 6> shadow_transforms = {
        shadow_projection * glm::lookAt(point_light.m_pos, point_light.m_pos + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
        shadow_projection * glm::lookAt(point_light.m_pos, point_light.m_pos + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
        shadow_projection * glm::lookAt(point_light.m_pos, point_light.m_pos + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
        shadow_projection * glm::lookAt(point_light.m_pos, point_light.m_pos + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)),
        shadow_projection * glm::lookAt(point_light.m_pos, point_light.m_pos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
        shadow_projection * glm::lookAt(point_light.m_pos, point_light.m_pos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f))};

    // Render scene to depth cubemap
    glViewport(
        0,
        0,
        point_light.m_buffer.m_dimension.x,
        point_light.m_buffer.m_dimension.y);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glBindFramebuffer(GL_FRAMEBUFFER, point_light.m_buffer.m_fbo);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ShaderUtilities::use(point_light.m_buffer.m_shader);
    for (unsigned int i = 0; i < 6; ++i)
    {
        ShaderUtilities::setMat4(
            point_light.m_buffer.m_shader,
            "shadow_matrices[" + std::to_string(i) + "]",
            shadow_transforms[i]);
    }
    ShaderUtilities::setVec3(
        point_light.m_buffer.m_shader,
        "light_pos",
        point_light.m_pos);
    ShaderUtilities::setFloat(
        point_light.m_buffer.m_shader,
        "far_plane",
        point_light.m_buffer.m_far);
}

void ShaderUtilities::configure_lighting(
    const GLuint p_shader) noexcept
{
    for (const std::pair<const std::size_t, DirectionalLight> &iter : LightingDb::dir_map)
    {
        ShaderUtilities::attach_dir_light(
            p_shader,
            iter.second);
    }
    for (const std::pair<const std::size_t, PointLight> &iter : LightingDb::point_map)
    {
        ShaderUtilities::attach_point_light(
            p_shader,
            iter.second);
    }
    for (const std::pair<const std::size_t, SpotLight> &iter : LightingDb::spot_map)
    {
        ShaderUtilities::attach_spot_light(
            p_shader,
            iter.second);
    }
    ShaderUtilities::setBool(
        p_shader,
        "enable_shadow",
        LightingDbWindow::enable_shadow);
    ShaderUtilities::setBool(
        p_shader,
        "enable_directional_light",
        LightingDbWindow::enable_directional_light);
    ShaderUtilities::setBool(
        p_shader,
        "enable_point_light",
        LightingDbWindow::enable_point_light);
    ShaderUtilities::setBool(
        p_shader,
        "enable_spot_light",
        LightingDbWindow::enable_spot_light);
    ShaderUtilities::setVec3(
        p_shader,
        "camera_position",
        AkarinCameraSystem::get_position());
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
