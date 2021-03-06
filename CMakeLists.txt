cmake_minimum_required(VERSION 3.10.2)

project(fatuous)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    fatuous
    
    src/main.cpp

    thirdparty/glad/src/glad.c
    thirdparty/imgui/imgui.cpp
    thirdparty/imgui/imgui_impl_glfw.cpp
    thirdparty/imgui/imgui_impl_opengl3.cpp
    thirdparty/imgui/imgui_widgets.cpp
    thirdparty/imgui/imgui_draw.cpp

    src/misc/shader_utilities.cpp
    src/misc/thread_pool.cpp
    src/misc/akarin_timer.cpp
    src/misc/opengl_settings.cpp

    src/systems/skybox_system.cpp
    src/systems/akarin_camera_system.cpp

    src/enums/shader_type.cpp
    src/enums/texture_type.cpp

    src/components/model.cpp
    src/components/model_info.cpp
    src/components/shader_file.cpp
    src/components/mesh_job.cpp
    src/components/mesh.cpp
    src/components/texture.cpp
    src/components/texture_info.cpp
    src/components/texture_job.cpp
    src/components/phong_light.cpp
    src/components/lighting.cpp
    src/components/intensity.cpp
    src/components/depth_buffer.cpp
    src/components/transform.cpp
    src/components/vertex.cpp
    
    src/akarin_database/texture/texture_database.cpp
    src/akarin_database/model/model_database.cpp
    src/akarin_database/mesh/mesh_database.cpp
    src/akarin_database/shader/shader_program.cpp
    src/akarin_database/shader/shader_database.cpp
    src/akarin_database/lighting/lighting_database.cpp
    
    src/akarin_database/glfw/akarin_glfw.cpp
    
    src/processes/entity_registry_master.cpp
    src/processes/rendering_process.cpp
    src/processes/swarm_process.cpp
    
    src/akarin_imgui/akarin_imgui.cpp
    src/akarin_imgui/model_database_window.cpp
    src/akarin_imgui/lighting_database_window.cpp
    src/akarin_imgui/entity_database_window.cpp
    src/akarin_imgui/shader_database_window.cpp
    src/akarin_imgui/opengl_settings_window.cpp)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_SOURCE_DIR}/thirdparty/glfw)

set(ASSIMP_BUILD_TESTS "" OFF)
add_subdirectory(${CMAKE_SOURCE_DIR}/thirdparty/assimp)

find_package(OpenGL REQUIRED)

include_directories(
    ${OPENGL_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/thirdparty
    ${CMAKE_SOURCE_DIR}/thirdparty/glm
    ${CMAKE_SOURCE_DIR}/thirdparty/glad
    ${CMAKE_SOURCE_DIR}/thirdparty/imgui
    ${CMAKE_SOURCE_DIR}/thirdparty/assimp
    ${CMAKE_SOURCE_DIR}/thirdparty/glad/include
    ${CMAKE_SOURCE_DIR}/thirdparty/entt/single_include )

target_link_libraries(fatuous ${OPENGL_LIBRARIES} glfw assimp)