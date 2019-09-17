#include "akarin_database/model/model_database.hpp"
#include "akarin_database/texture/texture_database.hpp"
#include "components/texture_job.hpp"
#include "akarin_database/mesh/mesh_database.hpp"
#include "components/vertex.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include <atomic>
#include <algorithm>
#include <unordered_map>
#include <chrono>
#include <ctime>
#include <future>
#include <thread>

// TODO :: How to implement a profiler??? I think by having a map of string and time, then check for their duration
void add_model(
    const Model &) noexcept;
bool contains(
    const std::string &) noexcept;
std::vector<std::size_t> load_material_textures(
    const std::string &,
    const aiMaterial *,
    const aiTextureType,
    const TextureType) noexcept;
void process_node(
    entt::registry &,
    const std::string &,
    const aiNode *,
    const aiScene *,
    std::vector<std::size_t> &) noexcept;
std::size_t process_mesh(
    entt::registry &,
    const std::string &,
    const aiMesh *,
    const aiScene *) noexcept;
std::unordered_map<std::size_t, Model> ModelDb::models_map;
std::atomic<std::size_t> m_model_id_counter = 1;

void ModelDb::add_model_job(
    entt::registry &p_reg,
    const std::string &p_model_path) noexcept
{
    const auto &find_model_iter = std::find_if(
        ModelDb::models_map.cbegin(),
        ModelDb::models_map.cend(),
        [p_model_path](const std::pair<const std::size_t, Model> &p_model_iter) -> bool {
            return p_model_iter.second.m_path == p_model_path;
        });
    if (find_model_iter != ModelDb::models_map.cend())
    {
        std::cout << "model:" << p_model_path << " already exists\n";
        return;
    }

    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(p_model_path, aiProcess_GenNormals | aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << "unable to load model error:" << importer.GetErrorString() << "\n";
        return;
    }

    const std::string model_root_directory = p_model_path.substr(
        0,
        p_model_path.find_last_of('/'));
    aiNode *root_node = scene->mRootNode;
    std::vector<std::size_t> meshes;
    process_node(
        p_reg,
        model_root_directory,
        root_node,
        scene,
        meshes);

    // TODO :: Must be deferred until Texture and Mesh are done with their shit.
    add_model(
        Model(
            p_model_path,
            meshes));
};

void process_node(
    entt::registry &p_reg,
    const std::string &p_model_root_directory,
    const aiNode *node,
    const aiScene *scene,
    std::vector<std::size_t> &meshes) noexcept
{
    for (std::size_t i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *ai_mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(process_mesh(
            p_reg,
            p_model_root_directory,
            ai_mesh,
            scene));
    }
    for (std::size_t i = 0; i < node->mNumChildren; i++)
    {
        process_node(
            p_reg,
            p_model_root_directory,
            node->mChildren[i],
            scene,
            meshes);
    }
};

std::size_t process_mesh(
    entt::registry &p_reg,
    const std::string &p_model_root_directory,
    const aiMesh *p_mesh,
    const aiScene *p_scene) noexcept
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<std::size_t> textures;

    for (std::size_t i = 0; i < p_mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 position;
        position.x = p_mesh->mVertices[i].x;
        position.y = p_mesh->mVertices[i].y;
        position.z = p_mesh->mVertices[i].z;
        vertex.position = position;

        glm::vec3 normal;
        normal.x = p_mesh->mNormals[i].x;
        normal.y = p_mesh->mNormals[i].y;
        normal.z = p_mesh->mNormals[i].z;
        vertex.normal = normal;

        if (p_mesh->mTextureCoords[0])
        {
            glm::vec2 tex_coord;
            tex_coord.x = p_mesh->mTextureCoords[0][i].x;
            tex_coord.y = p_mesh->mTextureCoords[0][i].y;
            vertex.tex_coord = tex_coord;
        }
        else
        {
            vertex.tex_coord = glm::vec2(0.0f, 0.0f);
        }

        if (p_mesh->mTangents)
        {
            glm::vec3 tangent;
            tangent.x = p_mesh->mTangents[i].x;
            tangent.y = p_mesh->mTangents[i].y;
            tangent.z = p_mesh->mTangents[i].z;
            vertex.tangent = tangent;
        }

        if (p_mesh->mBitangents)
        {
            glm::vec3 bitangent;
            bitangent.x = p_mesh->mBitangents[i].x;
            bitangent.y = p_mesh->mBitangents[i].y;
            bitangent.z = p_mesh->mBitangents[i].z;
            vertex.bitangent = bitangent;
        }

        vertices.push_back(vertex);
    }

    for (std::size_t i = 0; i < p_mesh->mNumFaces; i++)
    {
        aiFace face = p_mesh->mFaces[i];
        for (std::size_t j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    aiMaterial *material = p_scene->mMaterials[p_mesh->mMaterialIndex];

    std::vector<std::size_t> texture_diffuse_maps = load_material_textures(p_model_root_directory, material, aiTextureType_DIFFUSE, TextureType::DIFFUSE);
    textures.insert(textures.end(), texture_diffuse_maps.begin(), texture_diffuse_maps.end());
    std::vector<std::size_t> texture_specular_maps = load_material_textures(p_model_root_directory, material, aiTextureType_SPECULAR, TextureType::SPECULAR);
    textures.insert(textures.end(), texture_specular_maps.begin(), texture_specular_maps.end());
    std::vector<std::size_t> texture_normal_maps = load_material_textures(p_model_root_directory, material, aiTextureType_NORMALS, TextureType::NORMAL);
    textures.insert(textures.end(), texture_normal_maps.begin(), texture_normal_maps.end());
    std::vector<std::size_t> texture_height_maps = load_material_textures(p_model_root_directory, material, aiTextureType_HEIGHT, TextureType::HEIGHT);
    textures.insert(textures.end(), texture_height_maps.begin(), texture_height_maps.end());

    return MeshDb::add_mesh_job(p_reg, vertices, indices, textures);
};

std::vector<std::size_t> load_material_textures(
    const std::string &p_model_root_directory,
    const aiMaterial *p_ai_material,
    const aiTextureType p_ai_texture_type,
    const TextureType p_texture_type) noexcept
{
    std::vector<std::size_t> textures;
    auto tex_count = p_ai_material->GetTextureCount(p_ai_texture_type);
    for (std::uint32_t texture_iter = 0; texture_iter < tex_count; texture_iter++)
    {
        aiString str;
        p_ai_material->GetTexture(p_ai_texture_type, texture_iter, &str);
        const std::string texture_path = std::string(str.C_Str());
        textures.push_back(
            TextureDb::add_texture_job(
                p_model_root_directory + '/' + texture_path, p_texture_type));
    }
    return textures;
};

void add_model(
    const Model &p_modeldata) noexcept
{
    std::size_t model_id = m_model_id_counter++;
    ModelDb::models_map.emplace(
        model_id,
        p_modeldata);
};
