#pragma once
#include <functional>

#include "imgui.h"

using VoidCallback = std::function<void()>;

class Screen {
public:
    virtual ~Screen() = default;

    void render() {
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(1280, 720), ImGuiCond_Always);
        drawMainWindows();
        ImGui::End();
    }

    virtual void drawMainWindows() = 0;

    virtual void onShow() {
    }

    virtual void onHide() {
    }
};
