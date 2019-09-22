#include "components/depth_buffer.hpp"

#include "akarin_database/shader/shader_database.hpp"

DepthBuffer::DepthBuffer(
    const GLsizei p_m_width,
    const GLsizei p_m_height,
    const GLuint p_cube_map,
    const GLuint p_fbo,
    const GLuint p_shader)
    : m_width(p_m_width),
      m_height(p_m_height),
      m_cube_map(p_cube_map),
      m_fbo(p_fbo),
      m_shader(p_shader){};
