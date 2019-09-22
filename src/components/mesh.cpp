#include "components/mesh.hpp"
#include "akarin_database/shader/shader_database.hpp"

#include "glad/glad.h"

// FIXME :: This is not normalized data structure! ... Or is it?
Mesh::Mesh(
    const GLuint p_vao_gl_id,
    const GLuint p_vbo_gl_id,
    const GLuint p_ebo_gl_id,
    const std::vector<Vertex> &p_vertices,
    const std::vector<std::uint32_t> &p_indices,
    const std::vector<Texture> &p_textures) noexcept
    : m_vao_id(p_vao_gl_id),
      m_vbo_id(p_vbo_gl_id),
      m_ebo_id(p_ebo_gl_id),
      m_vertices(p_vertices),
      m_indices(p_indices),
      m_textures(p_textures){};

void Mesh::draw(
    const GLuint p_shader_id,
    bool draw_depth = false) const
{
    glBindVertexArray(m_vao_id);
    if (!draw_depth)
        ShaderDb::set_shader_program_texture(p_shader_id, m_textures);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
};
