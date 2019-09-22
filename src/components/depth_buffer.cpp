#include "components/depth_buffer.hpp"

#include "akarin_database/shader/shader_database.hpp"

DepthBuffer::DepthBuffer(
    const GLsizei p_m_height,
    const GLsizei p_m_width)
    : m_height(p_m_height),
      m_width(p_m_width)
{
    m_shader = ShaderDb::link_shader_files(
        {ShaderDb::load_shader_file(
             "./shaders/vertex/omnishadow.glsl",
             ShaderType::VERTEX),
         ShaderDb::load_shader_file(
             "./shaders/fragment/omnishadow.glsl",
             ShaderType::FRAGMENT),
         ShaderDb::load_shader_file(
             "./shaders/geometry/omnishadow.glsl",
             ShaderType::GEOMETRY)});

    // generate the cubemap
    glGenFramebuffers(1, &m_fbo);
    glGenTextures(1, &m_cube_map);

    // generate the single cubemap faces as 2d depth-valued texture images
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_cube_map);
    for (unsigned int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT,
                     m_width,
                     m_height,
                     0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    }
    // Set the texture parameters
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // Pass the cubemap as the depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_cube_map, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
};
