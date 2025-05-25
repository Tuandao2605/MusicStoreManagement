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

# MySQL
set(MYSQL_INCLUDE_DIR "C:\\Program Files\\MySQL\\MySQL Server 9.3\\include")
set(MYSQL_LIB_DIR "C:\\Program Files\\MySQL\\MySQL Server 9.3\\lib")

# Executable
add_executable(video-app
        src/main.cpp
        src/ui/core/screen.h
        src/ui/connect_db/connect_db_screen.h
        src/ui/connect_db/connect_db_screen.cpp
        src/music_store/music_repository.h
        src/music_store/music_repository.cpp
        src/ui/home/home_screen.h
        src/ui/add_new_item/add_item_screen.cpp
        src/ui/add_new_item/add_item_screen.h
        src/ui/all_items/show_all_items_screen.cpp
        src/ui/all_items/show_all_items_screen.h
        src/ui/item_in_stock/item_in_stock_screen.cpp
        src/ui/item_in_stock/item_in_stock_screen.h
        src/ui/find/find_music_screen.cpp
        src/ui/find/find_music_screen.h
        src/music_store/music_item.h
        src/music_store/helper.h
)

target_include_directories(imgui PUBLIC
        ${IMGUI_DIR}
        ${IMGUI_BACKENDS}
        ${CMAKE_SOURCE_DIR}/lib/glfw/include
)

target_include_directories(video-app PRIVATE ${MYSQL_INCLUDE_DIR})
target_link_directories(video-app PRIVATE ${MYSQL_LIB_DIR})
target_link_libraries(video-app PRIVATE imgui glfw OpenGL::GL mysql)