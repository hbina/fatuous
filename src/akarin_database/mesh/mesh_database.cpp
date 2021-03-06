#include "akarin_database/mesh/mesh_database.hpp"
#include "components/mesh_job.hpp"

#include "glad/glad.h"

#include <atomic>
#include <mutex>
#include <vector>

std::unordered_map<std::size_t, Mesh> MeshDb::map;

Mesh MeshDb::create_mesh(
    const std::vector<Vertex> &p_vertices,
    const std::vector<unsigned int> &p_indices,
    const std::vector<Texture> &p_textures) noexcept
{
    static std::atomic<std::size_t> mesh_id_counter = 1;
    const std::size_t mesh_id = mesh_id_counter++;
    GLuint mesh_vao_gl_id = 0;
    GLuint mesh_vbo_gl_id = 0;
    GLuint mesh_ebo_gl_id = 0;

    glGenVertexArrays(1, &mesh_vao_gl_id);
    glGenBuffers(1, &mesh_vbo_gl_id);
    glGenBuffers(1, &mesh_ebo_gl_id);

    glBindVertexArray(mesh_vao_gl_id);
    glBindBuffer(GL_ARRAY_BUFFER, mesh_vbo_gl_id);

    glBufferData(
        GL_ARRAY_BUFFER,
        p_vertices.size() * sizeof(Vertex),
        &p_vertices[0],
        GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_ebo_gl_id);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        p_indices.size() * sizeof(unsigned int),
        &p_indices[0],
        GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);

    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, m_normal));

    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, m_tex_coord));

    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, m_tangent));

    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, m_bitangent));

    glBindVertexArray(0);

    Mesh mesh = Mesh(
        mesh_vao_gl_id,
        mesh_vbo_gl_id,
        mesh_ebo_gl_id,
        p_vertices,
        p_indices,
        p_textures);
    map.emplace(
        std::make_pair(
            mesh_id,
            mesh));
    return mesh;
};