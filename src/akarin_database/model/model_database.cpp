#include "akarin_database/mesh/mesh_database.hpp"
#include "akarin_database/model/model_database.hpp"
#include "akarin_database/texture/texture_database.hpp"
#include "components/texture_job.hpp"
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
std::size_t add_model(
    const ModelInfo &) noexcept;
std::vector<Texture> load_material_textures(
    const std::string &,
    const aiMaterial *,
    const aiTextureType,
    const TextureType) noexcept;
void process_node(
    const std::string &,
    const aiNode *,
    const aiScene *,
    std::vector<Mesh> &) noexcept;
Mesh process_mesh(
    const std::string &,
    const aiMesh *,
    const aiScene *) noexcept;

std::unordered_map<std::size_t, ModelInfo> ModelDb::map;

std::size_t ModelDb::add_model_job(
    const std::string &p_model_path) noexcept
{
    const auto &find_model_iter = std::find_if(
        ModelDb::map.cbegin(),
        ModelDb::map.cend(),
        [p_model_path](const std::pair<const std::size_t, ModelInfo> &p_model_iter) -> bool {
            return p_model_iter.second.m_path == p_model_path;
        });
    if (find_model_iter != ModelDb::map.cend())
    {
        std::cout << "model:" << p_model_path << " already exists\n";
        return (*find_model_iter).first;
    }

    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(p_model_path, aiProcess_GenNormals | aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << "unable to load model error:" << importer.GetErrorString() << "\n";
        return 0; // TODO :: Make return default models
    }

    const std::string model_root_directory = p_model_path.substr(
        0,
        p_model_path.find_last_of('/'));
    aiNode *root_node = scene->mRootNode;
    std::vector<Mesh> meshes;
    process_node(
        model_root_directory,
        root_node,
        scene,
        meshes);

    // TODO :: Must be deferred until Texture and Mesh are done with their shit.
    return add_model(
        ModelInfo(
            p_model_path,
            meshes));
};

void process_node(
    const std::string &p_model_root_directory,
    const aiNode *node,
    const aiScene *scene,
    std::vector<Mesh> &meshes) noexcept
{
    for (std::size_t i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *ai_mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(process_mesh(
            p_model_root_directory,
            ai_mesh,
            scene));
    }
    for (std::size_t i = 0; i < node->mNumChildren; i++)
    {
        process_node(
            p_model_root_directory,
            node->mChildren[i],
            scene,
            meshes);
    }
};

Mesh process_mesh(
    const std::string &p_model_root_directory,
    const aiMesh *p_mesh,
    const aiScene *p_scene) noexcept
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for (std::size_t i = 0; i < p_mesh->mNumVertices; i++)
    {
        glm::vec3 position = glm::vec3(0.0f);
        position.x = p_mesh->mVertices[i].x;
        position.y = p_mesh->mVertices[i].y;
        position.z = p_mesh->mVertices[i].z;

        glm::vec3 normal = glm::vec3(0.0f);
        normal.x = p_mesh->mNormals[i].x;
        normal.y = p_mesh->mNormals[i].y;
        normal.z = p_mesh->mNormals[i].z;

        glm::vec2 tex_coord = glm::vec2(0.0f);
        if (p_mesh->mTextureCoords[0])
        {
            tex_coord.x = p_mesh->mTextureCoords[0][i].x;
            tex_coord.y = p_mesh->mTextureCoords[0][i].y;
        }

        glm::vec3 tangent = glm::vec3(0.0f);
        if (p_mesh->mTangents)
        {
            tangent.x = p_mesh->mTangents[i].x;
            tangent.y = p_mesh->mTangents[i].y;
            tangent.z = p_mesh->mTangents[i].z;
        }

        glm::vec3 bitangent = glm::vec3(0.0f);
        if (p_mesh->mBitangents)
        {
            bitangent.x = p_mesh->mBitangents[i].x;
            bitangent.y = p_mesh->mBitangents[i].y;
            bitangent.z = p_mesh->mBitangents[i].z;
        }

        vertices.emplace_back(
            position,
            normal,
            tangent,
            bitangent,
            tex_coord);
    }

    for (std::size_t i = 0; i < p_mesh->mNumFaces; i++)
    {
        aiFace face = p_mesh->mFaces[i];
        for (std::size_t j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    aiMaterial *material = p_scene->mMaterials[p_mesh->mMaterialIndex];

    std::vector<Texture> texture_diffuse_maps = load_material_textures(p_model_root_directory, material, aiTextureType_DIFFUSE, TextureType::DIFFUSE);
    for (const auto &iter : texture_diffuse_maps)
        textures.emplace_back(iter);
    std::vector<Texture> texture_specular_maps = load_material_textures(p_model_root_directory, material, aiTextureType_SPECULAR, TextureType::SPECULAR);
    for (const auto &iter : texture_specular_maps)
        textures.emplace_back(iter);
    std::vector<Texture> texture_normal_maps = load_material_textures(p_model_root_directory, material, aiTextureType_NORMALS, TextureType::NORMAL);
    for (const auto &iter : texture_normal_maps)
        textures.emplace_back(iter);
    std::vector<Texture> texture_height_maps = load_material_textures(p_model_root_directory, material, aiTextureType_HEIGHT, TextureType::HEIGHT);
    for (const auto &iter : texture_height_maps)
        textures.emplace_back(iter);

    return MeshDb::create_mesh(vertices, indices, textures);
};

std::vector<Texture> load_material_textures(
    const std::string &p_model_root_directory,
    const aiMaterial *p_ai_material,
    const aiTextureType p_ai_texture_type,
    const TextureType p_texture_type) noexcept
{
    std::vector<Texture> textures;
    auto tex_count = p_ai_material->GetTextureCount(p_ai_texture_type);
    for (std::uint32_t texture_iter = 0; texture_iter < tex_count; texture_iter++)
    {
        aiString str;
        p_ai_material->GetTexture(p_ai_texture_type, texture_iter, &str);
        const std::string texture_path = std::string(str.C_Str());
        textures.push_back(
            TextureDb::create_gl_texture(
                p_model_root_directory + '/' + texture_path,
                p_texture_type));
    }
    return textures;
};

std::size_t add_model(
    const ModelInfo &p_modeldata) noexcept
{
    static std::atomic<std::size_t> model_counter = 1;
    std::size_t model_id = model_counter++;
    ModelDb::map.emplace(
        model_id,
        p_modeldata);
    return model_id;
};
