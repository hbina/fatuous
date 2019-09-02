#include "akarin_database/mesh/mesh_data.hpp"
#include "akarin_database/shader_program_database.hpp"

#include "glad/glad.h"

// FIXME :: This is not normalized data structure! ... Or is it?
MeshData::MeshData(
    const unsigned int p_vao_gl_id,
    const unsigned int p_vbo_gl_id,
    const unsigned int p_ebo_gl_id,
    const std::vector<Vertex> &p_vertices,
    const std::vector<std::uint32_t> &p_indices,
    const std::vector<std::size_t> &p_textures) noexcept
    : m_vao_gl_id(p_vao_gl_id),
      m_vbo_gl_id(p_vbo_gl_id),
      m_ebo_gl_id(p_ebo_gl_id),
      m_vertices(p_vertices),
      m_indices(p_indices),
      m_textures(p_textures){};

void MeshData::draw(
    const std::size_t p_shader_id) const
{
    glBindVertexArray(m_vao_gl_id);
    ShaderProgramDatabase::set_shader_program_texture(p_shader_id, m_textures);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}