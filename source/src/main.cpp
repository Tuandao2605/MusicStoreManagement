#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <cstdio>

#include "music_store/music_repository.h"
#include "ui/add_new_item/add_item_screen.h"
#include "ui/all_items/show_all_items_screen.h"
#include "ui/connect_db/connect_db_screen.h"
#include "ui/core/screen.h"
#include "ui/find/find_music_screen.h"
#include "ui/home/home_screen.h"

// #include "music_store/music_repository.h"
// #include "ui/connect_db/connect_db_screen.h"
// #include "ui/core/screen.h"

Screen *current_screen = nullptr;
ConnectDbScreen *connect_db_screen = nullptr;
MusicRepository *music_repository = nullptr;
HomeScreen *home_screen = nullptr;
// ConnectDbScreen *connect_db_screen;
// MusicRepository *music_repository = nullptr;

static void glfw_error_callback(const int error, const char *description) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void showMyApplicationWindow();

void initGraph();

void clear();

int main(int, char **) {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

#if defined(__APPLE__)
    auto glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#endif

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);

    GLFWwindow *window = glfwCreateWindow(1280, 720, "Dear ImGui Test", nullptr, nullptr);
    if (window == nullptr) return 1;

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    const ImGuiIO &io = ImGui::GetIO();
    (void) io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    initGraph();
    music_repository = new MusicRepository();
    home_screen = new HomeScreen(
        [] { current_screen = new AddItemScreen(music_repository); },
        [] { current_screen = new ShowAllItemsScreen(music_repository); },
        [] {
        },
        [] {
            current_screen = new FindMusicScreen(music_repository, [] {
                current_screen = home_screen;
            });
        },
        [] {
        },
        [] {
        },
        [] {
        },
        [] {
        }
    );
    connect_db_screen = new ConnectDbScreen(music_repository, [] {
        current_screen = home_screen;
    });
    current_screen = connect_db_screen;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        showMyApplicationWindow();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    clear();
    return 0;
}


void showMyApplicationWindow() {
    current_screen->render();
    // if (current_screen) current_screen->render();
}

void initGraph() {
    // auto* music = new MusicRepository();
    // music->CreateOrder();
    // current_screen = connect_db_screen;
}

void clear() {
    // delete current_screen;
    // delete connect_db_screen;
    // delete music_repository;
}
