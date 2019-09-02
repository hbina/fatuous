cmake_minimum_required(VERSION 3.10)

project(akarin_engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options("/W4" "$<$<CONFIG:RELEASE>:/O0>")
else()
    add_compile_options("-Wall" "-g3" "$<$<CONFIG:RELEASE>:-O0>" "-Wno-unused-command-line-argument" "-lm")
endif()

add_executable(
    akarin_engine
    
    src/main.cpp

    include/external_submodules/glad/src/glad.c
    src/external_submodules/imgui/imgui.cpp
    src/external_submodules/imgui/imgui_impl_glfw.cpp
    src/external_submodules/imgui/imgui_impl_opengl3.cpp
    src/external_submodules/imgui/imgui_widgets.cpp
    src/external_submodules/imgui/imgui_draw.cpp

    src/tools/shader_utilities.cpp
    src/tools/thread_pool.cpp
    src/tools/akarin_profiler.cpp

    src/systems/input_system.cpp
    src/systems/skybox_system.cpp
    src/systems/akarin_camera_system.cpp
    
    src/akarin_database/texture/texture_data.cpp
    src/akarin_database/texture/texture_database.cpp
    
    src/akarin_database/model/model_data.cpp
    src/akarin_database/model/model_database.cpp

    src/akarin_database/mesh/mesh_job.cpp
    src/akarin_database/mesh/mesh_data.cpp
    src/akarin_database/mesh/mesh_database.cpp


    src/akarin_database/shader_code_database.cpp
    src/akarin_database/shader_program_database.cpp
    
    src/processes/ecs_master_process.cpp
    src/processes/rendering_process.cpp
    src/processes/swarm_process.cpp

    src/types/texture.cpp
    
    src/akarin_imgui/akarin_imgui.cpp
    src/akarin_imgui/model_database_window.cpp
    src/akarin_imgui/lighting_database_window.cpp
    src/akarin_imgui/entity_database_window.cpp
    src/akarin_imgui/shader_code_database_window.cpp
    src/akarin_imgui/shader_program_database_window.cpp)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_SOURCE_DIR}/include/external_submodules/glfw)

set(ASSIMP_BUILD_TESTS "" OFF)
add_subdirectory(${CMAKE_SOURCE_DIR}/include/external_submodules/assimp)

add_subdirectory(${CMAKE_SOURCE_DIR}/include/external_submodules/entt)

find_package(OpenGL REQUIRED)

include_directories(
    ${OPENGL_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/external_submodules 
    ${CMAKE_SOURCE_DIR}/include/external_submodules/glm
    ${CMAKE_SOURCE_DIR}/include/external_submodules/imgui
    ${CMAKE_SOURCE_DIR}/include/external_submodules/imgui/examples
    ${CMAKE_SOURCE_DIR}/include/external_submodules/glad/include
    ${CMAKE_SOURCE_DIR}/include/external_submodules/entt/single_include )

target_link_libraries(akarin_engine ${OPENGL_LIBRARIES} glfw assimp)