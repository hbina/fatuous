#include "systems/akarin_camera_system.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GLFW/glfw3.h"

// Should have its own ImGui window
struct AkarinCamera
{
    glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 m_front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 m_right = glm::vec3(-1.0f, 0.0f, 0.0f);
    glm::vec3 m_world_up = glm::vec3(0.0f, 1.0f, 0.0f);
    float m_yaw = -90.0f;
    float m_pitch = 0.0f;
    float m_speed = 250.0f;
    float m_sensitivity = 2.0f;
    float m_zoom = 45.0f;
    float clip_near = 0.1f;
    float clip_far = 10000.0f;

    auto update_camera_vectors() noexcept -> void
    {
        glm::vec3 front;
        front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        front.y = sin(glm::radians(m_pitch));
        front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        m_front = glm::normalize(front);
        m_right = glm::normalize(glm::cross(m_front, m_world_up));
        m_up = glm::normalize(glm::cross(m_right, m_front));
    };

    auto get_view_matrix() const noexcept -> glm::mat4
    {

        return glm::lookAt(m_position, m_position + m_front, m_up);
    };
} akarin_camera;

auto AkarinCameraSystem::process_keyboard(
    AkarinGLFW &p_glfw,
    const float p_delta_time) noexcept -> void
{
    // TODO :: Make this our enum.
    float velocity = akarin_camera.m_speed * p_delta_time;
    if (p_glfw.is_pressed(GLFW_KEY_W) || p_glfw.is_repeated(GLFW_KEY_W))
    {
        akarin_camera.m_position += akarin_camera.m_front * velocity;
    }
    if (p_glfw.is_pressed(GLFW_KEY_S) || p_glfw.is_repeated(GLFW_KEY_S))
    {
        akarin_camera.m_position -= akarin_camera.m_front * velocity;
    }
    if (p_glfw.is_pressed(GLFW_KEY_A) || p_glfw.is_repeated(GLFW_KEY_A))
    {
        akarin_camera.m_position -= akarin_camera.m_right * velocity;
    }
    if (p_glfw.is_pressed(GLFW_KEY_D) || p_glfw.is_repeated(GLFW_KEY_D))
    {
        akarin_camera.m_position += akarin_camera.m_right * velocity;
    }
    if (p_glfw.is_pressed(GLFW_KEY_UP) || p_glfw.is_repeated(GLFW_KEY_UP))
    {
        akarin_camera.m_pitch += p_delta_time * 100.0f;
    }
    if (p_glfw.is_pressed(GLFW_KEY_DOWN) || p_glfw.is_repeated(GLFW_KEY_DOWN))
    {
        akarin_camera.m_pitch -= p_delta_time * 100.0f;
    }
    if (p_glfw.is_pressed(GLFW_KEY_RIGHT) || p_glfw.is_repeated(GLFW_KEY_RIGHT))
    {
        akarin_camera.m_yaw += p_delta_time * 100.0f;
    }
    if (p_glfw.is_pressed(GLFW_KEY_LEFT) || p_glfw.is_repeated(GLFW_KEY_LEFT))
    {
        akarin_camera.m_yaw -= p_delta_time * 100.0f;
    }

    if (akarin_camera.m_pitch > 88.0f)
        akarin_camera.m_pitch = 88.0f;
    if (akarin_camera.m_pitch < -88.0f)
        akarin_camera.m_pitch = -88.0f;
    akarin_camera.update_camera_vectors();
};

glm::mat4 AkarinCameraSystem::get_projection(
    const AkarinGLFW &p_glfw) noexcept
{
    return glm::perspective(
        glm::radians(akarin_camera.m_zoom),
        p_glfw.get_window_size_ratio(),
        akarin_camera.clip_near,
        akarin_camera.clip_far);
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
