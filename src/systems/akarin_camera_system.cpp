#include "systems/akarin_camera_system.hpp"
#include "akarin_database/singleton/glfw/akarin_glfw.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GLFW/glfw3.h"

struct
{
    glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 50.0f);
    glm::vec3 m_front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 m_right = glm::vec3(-1.0f, 0.0f, 0.0f);
    glm::vec3 m_world_up = glm::vec3(0.0f, 1.0f, 0.0f);
    double m_yaw = -90.0f;
    double m_pitch = 0.0f;
    double m_speed = 250.0f;
    double m_sensitivity = 2.0f;
    double m_zoom = 45.0f;

    void update_camera_vectors() noexcept
    {
        glm::vec3 front;
        front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        front.y = sin(glm::radians(m_pitch));
        front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        m_front = glm::normalize(front);
        m_right = glm::normalize(glm::cross(m_front, m_world_up));
        m_up = glm::normalize(glm::cross(m_right, m_front));
    };

    glm::mat4 get_view_matrix() const noexcept
    {

        return glm::lookAt(m_position, m_position + m_front, m_up);
    };
} akarin_camera;

void AkarinCameraSystem::process_keyboard(const double p_delta_time) noexcept
{
    // TODO :: Make this our enum.
    float velocity = static_cast<float>(akarin_camera.m_speed * p_delta_time);
    if (AkarinGLFW::is_pressed(GLFW_KEY_W) || AkarinGLFW::is_repeated(GLFW_KEY_W))
    {
        akarin_camera.m_position += akarin_camera.m_front * velocity;
    }
    if (AkarinGLFW::is_pressed(GLFW_KEY_S) || AkarinGLFW::is_repeated(GLFW_KEY_S))
    {
        akarin_camera.m_position -= akarin_camera.m_front * velocity;
    }
    if (AkarinGLFW::is_pressed(GLFW_KEY_A) || AkarinGLFW::is_repeated(GLFW_KEY_A))
    {
        akarin_camera.m_position -= akarin_camera.m_right * velocity;
    }
    if (AkarinGLFW::is_pressed(GLFW_KEY_D) || AkarinGLFW::is_repeated(GLFW_KEY_D))
    {
        akarin_camera.m_position += akarin_camera.m_right * velocity;
    }
    if (AkarinGLFW::is_pressed(GLFW_KEY_UP) || AkarinGLFW::is_repeated(GLFW_KEY_UP))
    {
        akarin_camera.m_pitch += p_delta_time * 100.0f;
    }
    if (AkarinGLFW::is_pressed(GLFW_KEY_DOWN) || AkarinGLFW::is_repeated(GLFW_KEY_DOWN))
    {
        akarin_camera.m_pitch -= p_delta_time * 100.0f;
    }
    if (AkarinGLFW::is_pressed(GLFW_KEY_RIGHT) || AkarinGLFW::is_repeated(GLFW_KEY_RIGHT))
    {
        akarin_camera.m_yaw += p_delta_time * 100.0f;
    }
    if (AkarinGLFW::is_pressed(GLFW_KEY_LEFT) || AkarinGLFW::is_repeated(GLFW_KEY_LEFT))
    {
        akarin_camera.m_yaw -= p_delta_time * 100.0f;
    }

    if (akarin_camera.m_pitch > 88.0f)
        akarin_camera.m_pitch = 88.0f;
    if (akarin_camera.m_pitch < -88.0f)
        akarin_camera.m_pitch = -88.0f;
    akarin_camera.update_camera_vectors();
};

glm::mat4 AkarinCameraSystem::get_projection() noexcept
{
    return glm::perspective(
        static_cast<float>(glm::radians(akarin_camera.m_zoom)),
        static_cast<float>(AkarinGLFW::get_window_size_ratio()), // TODO :: Temporary, later will make them all doubles
        0.1f,
        20000.0f); // TODO :: Make projection part fo the camera member variables
}

glm::mat4 AkarinCameraSystem::get_view() noexcept
{
    return akarin_camera.get_view_matrix();
}

glm::vec3 AkarinCameraSystem::get_position() noexcept
{
    return akarin_camera.m_position;
};

glm::vec3 AkarinCameraSystem::get_front() noexcept
{
    return akarin_camera.m_front;
};
