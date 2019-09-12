#include "misc/opengl_settings.hpp"
#include "misc/akarin_macros.hpp"
#include "akarin_database/singleton/glfw/akarin_glfw.hpp"

#include "glad/glad.h"

#include <iostream>

bool changed = true;

// Depth stuff
bool enable_depth_buffer = true;
DepthFun current_depth_buffer_func = DepthFun::LESS;

bool enable_cull_face = true;
CullFace current_cull_face = CullFace::BACK;

void OpenGLSettings::update() noexcept
{
    // Not sure if OpenGsL likes it when we just change whenever?
    if (changed)
    {
        changed = false;
        // TODO :: Make these its own thing
        update_cull_face();
        update_depth_function();
    }
};

void OpenGLSettings::enable(const GLEnum p_enum, const bool p_enable) noexcept
{
    changed = true;
    switch (p_enum)
    {
    case GLEnum::DEPTH_TEST:
    {
        enable_depth_buffer = p_enable;
        break;
    }
    case GLEnum::CULL_FACE:
    {
        enable_cull_face = p_enable;
        break;
    }
    default:
    {
        UNHANDLED_SWITCH_CASE(__LINE__, __FILE__);
    }
    };
};

void OpenGLSettings::update_depth_function() noexcept
{
    if (!enable_depth_buffer)
    {
        glDisable(GL_DEPTH_TEST);
        return;
    }

    glEnable(GL_DEPTH_TEST);
    switch (current_depth_buffer_func)
    {
    case DepthFun::ALWAYS:
    {
        glDepthFunc(GL_ALWAYS);
        break;
    };
    case DepthFun::EQUAL:
    {
        glDepthFunc(GL_EQUAL);
        break;
    };
    case DepthFun::GEQUAL:
    {
        glDepthFunc(GL_GEQUAL);
        break;
    };
    case DepthFun::GREATER:
    {
        glDepthFunc(GL_GREATER);
        break;
    };
    case DepthFun::LEQUAL:
    {
        glDepthFunc(GL_LEQUAL);
        break;
    };
    case DepthFun::LESS:
    {
        glDepthFunc(GL_LESS);
        break;
    };
    case DepthFun::NEVER:
    {
        glDepthFunc(GL_NEVER);
        break;
    };
    case DepthFun::NOTEQUAL:
    {
        glDepthFunc(GL_NOTEQUAL);
        break;
    };
    default:
    {
        UNHANDLED_SWITCH_CASE(__LINE__, __FILE__);
    };
    }
};

void OpenGLSettings::set_depth_function(const DepthFun p_func_type) noexcept
{
    if (p_func_type == current_depth_buffer_func)
        return;
    changed = true;
    current_depth_buffer_func = p_func_type;
};

void OpenGLSettings::set_cull_face(const CullFace p_cull_face) noexcept
{
    if (p_cull_face == current_cull_face)
        return;
    changed = true;
    current_cull_face = p_cull_face;
};

void OpenGLSettings::update_cull_face() noexcept
{
    if (!enable_cull_face)
    {
        glDisable(GL_CULL_FACE);
        return;
    }

    glEnable(GL_CULL_FACE);
    switch (current_cull_face)
    {
    case CullFace::BACK:
    {
        glCullFace(GL_BACK);
        break;
    };
    case CullFace::FRONT:
    {
        glCullFace(GL_FRONT);
        break;
    };
    case CullFace::FRONT_AND_BACK:
    {
        glCullFace(GL_FRONT_AND_BACK);
        break;
    };
    default:
    {
        UNHANDLED_SWITCH_CASE(__LINE__, __FILE__);
    };
    }
};

GLbitfield get_clear_mask()
{
    GLbitfield result = GL_COLOR_BUFFER_BIT;
    if (enable_depth_buffer)
        result |= GL_DEPTH_BUFFER_BIT;
    return result;
};

void OpenGLSettings::gl_clear() noexcept
{
    glViewport(0, 0, AkarinGLFW::window_dimension.x, AkarinGLFW::window_dimension.y);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(get_clear_mask());
}