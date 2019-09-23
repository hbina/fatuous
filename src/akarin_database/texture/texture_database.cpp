#include "akarin_database/texture/texture_database.hpp"
#include "misc/akarin_macros.hpp"

#include "glad/glad.h"
#include "stb/stb_image.h"

#include <algorithm>
#include <atomic>
#include <iostream>
#include <mutex>
#include <vector>

std::unordered_map<GLuint, TextureInfo> TextureDb::map;

Texture TextureDb::create_gl_texture(
    const std::string &p_path,
    const TextureType p_type) noexcept
{
    GLuint texture_gl_id;
    glGenTextures(1, &texture_gl_id);

    int texture_width = 0;
    int texture_height = 0;
    int texture_channels = 0;
    unsigned char *data = stbi_load(
        p_path.c_str(),
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
        std::cerr << "texture failed to load at p_path: " << p_path << "\n";
        stbi_image_free(data);
    }

    TextureDb::map.emplace(
        std::make_pair(
            texture_gl_id,
            TextureInfo(
                texture_gl_id,
                p_type,
                p_path,
                {texture_width, texture_height})));
    return Texture(texture_gl_id, p_type);
};

GLuint TextureDb::load_cube_texture(
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
    TextureDb::map.emplace(
        std::make_pair(
            texture_gl_id,
            TextureInfo(
                texture_gl_id,
                TextureType::CUBE_MAP,
                textures_folder_dir,
                {texture_width, texture_height, texture_channels})));
    return texture_gl_id;
};
