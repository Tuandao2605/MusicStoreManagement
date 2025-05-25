cmake_minimum_required(VERSION 3.14)
project(video-app C CXX)
set(CMAKE_CXX_STANDARD 20)

# ImGui
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/lib/imgui)
set(IMGUI_BACKENDS ${IMGUI_DIR}/backends)
set(IMGUI_SRC
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_BACKENDS}/imgui_impl_glfw.cpp
        ${IMGUI_BACKENDS}/imgui_impl_opengl3.cpp
)
add_library(imgui STATIC ${IMGUI_SRC})
target_include_directories(imgui PUBLIC ${IMGUI_DIR} ${IMGUI_BACKENDS})

# GLFW
add_subdirectory(lib/glfw)

# OpenGL
find_package(OpenGL REQUIRED)

# Executable
add_executable(video-app
        src/main.cpp
)
target_include_directories(imgui PUBLIC
        ${IMGUI_DIR}
        ${IMGUI_BACKENDS}
        ${CMAKE_SOURCE_DIR}/lib/glfw/include
)

target_link_libraries(video-app PRIVATE imgui glfw OpenGL::GL)

