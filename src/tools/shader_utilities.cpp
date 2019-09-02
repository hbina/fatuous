#include "tools/shader_utilities.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glad/glad.h"
#include "glm/glm.hpp"


// TODO :: Consider putting this into akarin_database/

void ShaderUtilities::use(
    const std::size_t p_shader_program_id) noexcept
{
    glUseProgram(p_shader_program_id);
};

void ShaderUtilities::transform_shader(
    const std::size_t shader_program_id,
    const glm::mat4 &p_projection,
    const glm::mat4 &p_view,
    const glm::vec3 &p_position,
    const glm::vec3 &p_scale) noexcept

{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, p_position);
    model = glm::scale(model, p_scale);
    // TODO :: Add rotation to Transform
    ShaderUtilities::setMat4(shader_program_id, "model", model);
    ShaderUtilities::setMat4(shader_program_id, "projection_view_model", p_projection * p_view * model);
};

void ShaderUtilities::setBool(
    const std::size_t p_shader_program_id,
    const std::string &p_property_name,
    const bool p_value) noexcept
{
    glUniform1i(glGetUniformLocation(p_shader_program_id, p_property_name.c_str()), (int)p_value);
};

void ShaderUtilities::setInt(
    const std::size_t p_shader_program_id,
    const std::string &p_property_name,
    const int p_value) noexcept
{
    glUniform1i(glGetUniformLocation(p_shader_program_id, p_property_name.c_str()), p_value);
};

void ShaderUtilities::setFloat(
    const std::size_t p_shader_program_id,
    const std::string &p_property_name,
    const float p_value) noexcept
{
    glUniform1f(glGetUniformLocation(p_shader_program_id, p_property_name.c_str()), p_value);
};

void ShaderUtilities::setVec2(
    const std::size_t p_shader_program_id,
    const std::string &p_property_name,
    const glm::vec2 &p_value) noexcept
{
    glUniform2fv(glGetUniformLocation(p_shader_program_id, p_property_name.c_str()), 1, &p_value[0]);
};

void ShaderUtilities::setVec2(
    const std::size_t p_shader_program_id,
    const std::string &p_property_name,
    const std::array<float, 2> &p_array) noexcept
{
    glUniform2f(glGetUniformLocation(p_shader_program_id, p_property_name.c_str()), p_array[0], p_array[1]);
};

void ShaderUtilities::setVec3(
    const std::size_t p_shader_program_id,
    const std::string &p_property_name,
    const glm::vec3 &p_value) noexcept
{
    glUniform3fv(glGetUniformLocation(p_shader_program_id, p_property_name.c_str()), 1, &p_value[0]);
};

void ShaderUtilities::setVec3(
    const std::size_t p_shader_program_id,
    const std::string &p_property_name,
    const std::array<float, 3> &p_array) noexcept
{
    glUniform3f(glGetUniformLocation(p_shader_program_id, p_property_name.c_str()), p_array[0], p_array[1], p_array[2]);
};

void ShaderUtilities::setVec4(
    const std::size_t p_shader_program_id,
    const std::string &p_property_name,
    const glm::vec4 &p_value) noexcept
{
    glUniform4fv(glGetUniformLocation(p_shader_program_id, p_property_name.c_str()), 1, &p_value[0]);
};

void ShaderUtilities::setVec4(
    const std::size_t p_shader_program_id,
    const std::string &p_property_name,
    const std::array<float, 4> &p_array) noexcept
{
    glUniform4f(glGetUniformLocation(p_shader_program_id, p_property_name.c_str()), p_array[0], p_array[1], p_array[2], p_array[3]);
};

void ShaderUtilities::setMat2(
    const std::size_t p_shader_program_id,
    const std::string &p_property_name,
    const glm::mat2 &p_value) noexcept
{
    glUniformMatrix2fv(glGetUniformLocation(p_shader_program_id, p_property_name.c_str()), 1, GL_FALSE, &p_value[0][0]);
};

void ShaderUtilities::setMat3(
    const std::size_t p_shader_program_id,
    const std::string &p_property_name,
    const glm::mat3 &p_value) noexcept
{
    glUniformMatrix3fv(glGetUniformLocation(p_shader_program_id, p_property_name.c_str()), 1, GL_FALSE, &p_value[0][0]);
};

void ShaderUtilities::setMat4(
    const std::size_t p_shader_program_id,
    const std::string &p_property_name,
    const glm::mat4 &p_value) noexcept
{
    glUniformMatrix4fv(glGetUniformLocation(p_shader_program_id, p_property_name.c_str()), 1, GL_FALSE, &p_value[0][0]);
};
