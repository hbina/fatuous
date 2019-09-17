#include "akarin_database/mesh/mesh_database.hpp"
#include "components/mesh_job.hpp"

#include "glad/glad.h"

#include <atomic>
#include <mutex>
#include <vector>

// std::unordered_map<std::size_t, Mesh> MeshDb::meshes_map;

std::atomic<std::size_t> mesh_id_counter = 1;

void execute_job(
    entt::registry &,
    const MeshJob &) noexcept;

std::size_t MeshDb::add_mesh_job(
    entt::registry &p_reg,
    const std::vector<Vertex> &p_vertices,
    const std::vector<unsigned int> &p_indices,
    const std::vector<std::size_t> &p_textures) noexcept
{
    const std::size_t mesh_id = mesh_id_counter++;
    p_reg.assign<MeshJob>(
        p_reg.create(),
        mesh_id,
        p_vertices,
        p_indices,
        p_textures);
    return mesh_id;
};

void MeshDb::execute_jobs(
    entt::registry &p_reg) noexcept
{
    p_reg.view<MeshJob>()
        .each([&](
                  const entt::entity &e,
                  const MeshJob &mesh_job) {
            execute_job(p_reg, mesh_job);
            p_reg.destroy(e);
        });
};

void execute_job(
    entt::registry &p_reg,
    const MeshJob &p_mesh_job) noexcept
{
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
        p_mesh_job.m_vertices.size() * sizeof(Vertex),
        &p_mesh_job.m_vertices[0],
        GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_ebo_gl_id);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        p_mesh_job.m_indices.size() * sizeof(unsigned int),
        &p_mesh_job.m_indices[0],
        GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);

    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));

    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, tex_coord));

    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, tangent));

    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, bitangent));

    glBindVertexArray(0);

    p_reg.assign<Mesh>(
        p_reg.create(),
        p_mesh_job.m_id,
        mesh_vao_gl_id,
        mesh_vbo_gl_id,
        mesh_ebo_gl_id,
        p_mesh_job.m_vertices,
        p_mesh_job.m_indices,
        p_mesh_job.m_textures);
};
