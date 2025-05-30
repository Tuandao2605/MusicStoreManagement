#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <cstdio>

#include "music_store/music_repository.h"
#include "ui/all_items/show_all_items_screen.h"
#include "ui/connect_db/connect_db_screen.h"
#include "ui/core/screen.h"
#include "ui/order_item/order_item_screen.h"

Screen *current_screen = nullptr;
ConnectDbScreen *connect_db_screen = nullptr;
MusicRepository *music_repository = nullptr;
ShowAllItemsScreen *show_all_items_screen = nullptr;
OrderItemScreen *order_item_screen = nullptr;

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


void createOrderItemScreen(const std::string &item_id) {
    if (order_item_screen) {
        delete order_item_screen;
    }
    order_item_screen = new OrderItemScreen(item_id, music_repository, [] {
        current_screen = show_all_items_screen;
    });
}


void initGraph() {
    music_repository = new MusicRepository();

    connect_db_screen = new ConnectDbScreen(music_repository, [] { current_screen = show_all_items_screen; });

    show_all_items_screen = new ShowAllItemsScreen(music_repository,
                                                   [] { current_screen = connect_db_screen; },
                                                   [](const std::string &item_id) {
                                                       createOrderItemScreen(item_id);
                                                       current_screen = order_item_screen;
                                                   });
    current_screen = connect_db_screen;
}

void clear() {
    delete connect_db_screen;
    delete music_repository;
    delete show_all_items_screen;
    delete order_item_screen;
}
