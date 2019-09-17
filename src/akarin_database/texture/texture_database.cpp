#include "akarin_database/texture/texture_database.hpp"
#include "misc/akarin_macros.hpp"

#include "glad/glad.h"
#include "stb/stb_image.h"

#include <algorithm>
#include <atomic>
#include <iostream>
#include <mutex>
#include <vector>

std::mutex texture_job_mutex;
std::vector<TextureJob> texture_jobs;

std::unordered_map<std::size_t, TextureInfo> TextureDb::textures_map;
std::atomic<std::size_t> texture_counter = 1;

std::size_t TextureDb::add_texture_job(
    const std::string &p_texture_filepath,
    const TextureType p_texture_type) noexcept
{
    const auto &texture_iter = std::find_if(
        textures_map.cbegin(),
        textures_map.cend(),
        [p_texture_filepath](
            const std::pair<const std::size_t, TextureInfo> &p_texture_iter) {
            return p_texture_iter.second.m_path == p_texture_filepath;
        });
    if (texture_iter == textures_map.end())
    {
        std::lock_guard<std::mutex> lock(texture_job_mutex);
        const auto &texture_id = texture_counter++;
        texture_jobs.push_back(
            TextureJob(
                texture_id,
                p_texture_filepath,
                p_texture_type));
        return texture_id;
    }
    else
    {
        return (*texture_iter).first;
    }
};

void TextureDb::execute_jobs() noexcept
{
    std::lock_guard<std::mutex> lock(texture_job_mutex);
    std::for_each(
        texture_jobs.cbegin(),
        texture_jobs.cend(),
        [](const TextureJob &p_intermediate_texture) {
            create_gl_texture(p_intermediate_texture);
        });
    texture_jobs.clear();
};

Texture create_gl_texture(const TextureJob &p_texture_job) noexcept
{
    GLuint texture_gl_id;
    glGenTextures(1, &texture_gl_id);

    int texture_width = 0;
    int texture_height = 0;
    int texture_channels = 0;
    unsigned char *data = stbi_load(
        p_texture_job.m_path.c_str(),
        &texture_width,
        &texture_height,
        &texture_channels,
        0);

    if (data)
    {
        GLenum format = GL_RED;
        GLenum internal_format = GL_R8;
        switch (texture_channels)
        {
        case 1:
        {
            format = GL_RED;
            internal_format = GL_R8;
            break;
        }
        case 3:
        {
            format = GL_RGB;
            internal_format = GL_SRGB8;
            break;
        }
        case 4:
        {
            format = GL_RGBA;
            internal_format = GL_SRGB8_ALPHA8;
            break;
        }
        default:
        {
            UNHANDLED_SWITCH_CASE(__LINE__, __FILE__);
        }
        }

        glBindTexture(GL_TEXTURE_2D, texture_gl_id);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            internal_format,
            texture_width,
            texture_height,
            0,
            format,
            GL_UNSIGNED_BYTE,
            data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        // TODO :: Since this is nullable type, please introduce a default texture!
        std::cerr << "texture failed to load at p_texture_job.m_path: " << p_texture_job.m_path << "\n";
        stbi_image_free(data);
    }

    TextureDb::textures_map.emplace(
        std::make_pair(
            p_texture_job.m_id,
            TextureInfo(
                texture_gl_id,
                p_texture_job.m_type,
                p_texture_job.m_path,
                {texture_width, texture_height})));
};

Texture TextureDb::load_cube_texture(
    const std::array<std::string, 6> &faces) noexcept
{
    GLuint texture_gl_id = 0;
    glGenTextures(1, &texture_gl_id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture_gl_id);

    int texture_width, texture_height, texture_channels;
    for (GLenum i = 0; i < faces.size(); i++)
    {
        GLvoid *data = stbi_load(
            faces[i].c_str(),
            &texture_width,
            &texture_height,
            &texture_channels,
            0);
        if (data)
        {
            glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0,
                GL_RGB,
                texture_width,
                texture_height,
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                data);
            stbi_image_free(data);
        }
        else
        {
            std::cerr << "cubemap texture failed to load at path: " << faces[i] << "\n";
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    std::string textures_folder_dir = std::string(
        std::string(faces[0]).substr(0),
        std::string(faces[0]).find_last_of('/'));
    std::lock_guard<std::mutex> lock(texture_job_mutex);
    const auto &texture_id = texture_counter++;
    TextureDb::textures_map.emplace(
        std::make_pair(
            texture_id,
            TextureInfo(
                texture_gl_id,
                TextureType::CUBE_MAP,
                textures_folder_dir,
                {texture_width, texture_height, texture_channels})));
    return Texture(texture_id);
};
