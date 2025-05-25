cmake_minimum_required(VERSION 3.14)
project(video-app C CXX)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib/imgui)
add_subdirectory(lib/glfw)

set(MYSQL_INCLUDE_DIR "C:\\Program Files\\MySQL\\MySQL Server 9.3\\include")


add_definitions(-DGL_SILENCE_DEPRECATION)

list(APPEND SOURCES
        src/main.cpp
)

add_executable(untitled WIN32 ${SOURCES}
        src/ui/core/Screen.h
        src/music_store/music_repository.cpp
        src/music_store/music_repository.h
        src/ui/connect_db/connect_db_screen.cpp
        src/ui/connect_db/connect_db_screen.h)

target_include_directories(untitled PUBLIC
        ${GLFW_INCLUDE_DIRS}
        ${MYSQL_INCLUDE_DIR}
)

link_directories(${GLFW_LIBRARY_DIRS})

if (APPLE)
    list(APPEND EXTRA_LIBS
            "-framework OpenGL"
    )
elseif (WIN32)
    list(APPEND EXTRA_LIBS
            glu32
            opengl32
    )
else ()
    list(APPEND EXTRA_LIBS
            GL
            GLU
            X11
    )
endif ()

target_link_libraries(untitled
        imgui
        ${GLFW_LIBRARIES}
        ${EXTRA_LIBS}
        "C:\\Program Files\\MySQL\\MySQL Server 9.3\\lib\\libmysqlclient.lib"
)
