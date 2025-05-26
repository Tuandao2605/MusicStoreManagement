#pragma once
#include <functional>

#include "imgui.h"

using VoidCallback = std::function<void()>;

class Screen {
    std::string title;

public:
    explicit Screen(const std::string &title) : title(title) {
    }

    virtual ~Screen() = default;

    void render() {
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(1280, 720), ImGuiCond_Always);
        ImGui::Begin(title.c_str());
        drawMainWindows();
        ImGui::End();
    }

    virtual void drawMainWindows() = 0;

    virtual void onShow() {
    }

    virtual void onHide() {
    }
};
