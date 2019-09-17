#include "components/mesh_data.hpp"
#include "akarin_database/shader/shader_database.hpp"

#include "glad/glad.h"

// FIXME :: This is not normalized data structure! ... Or is it?
MeshData::MeshData(
    const GLuint p_vao_gl_id,
    const GLuint p_vbo_gl_id,
    const GLuint p_ebo_gl_id,
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
    const GLuint p_shader_id,
    bool draw_depth = false) const
{
    glBindVertexArray(m_vao_gl_id);
    if (!draw_depth)
        ShaderDb::set_shader_program_texture(p_shader_id, m_textures);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}