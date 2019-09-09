#include "misc/opengl_settings.hpp"

#include "glad/glad.h"

#include <iostream>

bool changed = true;
bool enable_depth_buffer = true;
DepthFun current_depth_buffer_function = DepthFun::LESS;

void OpenGLSettings::update() noexcept
{
    // Not sure if OpenGsL likes it when we just change whenever?
    if (changed)
    {
        changed = false;
        // TODO :: Make these its own thing
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

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
    default:
    {
        std::cerr << "unhandled switch case at line " << __LINE__ << __FILE__ << std::endl;
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
    switch (current_depth_buffer_function)
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
        std::cerr << "unhandled switch case " << __LINE__ << __FILE__ << std::endl;
    };
    }
};

void OpenGLSettings::set_depth_function(const DepthFun p_func_type) noexcept
{
    changed = true;
    current_depth_buffer_function = p_func_type;
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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(get_clear_mask());
}