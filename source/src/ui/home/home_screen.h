#pragma once
#include "imgui.h"
#include "../core/screen.h"

class HomeScreen final : public Screen {
public:
    HomeScreen(): Screen() {
    }

    void render() override {
        ImGui::Begin("Home Screen");

        if (ImGui::Button("Add New Item In Database")) {
        }

        if (ImGui::Button("Show All Items")) {
        }

        if (ImGui::Button("Item In Stock")) {
        }

        if (ImGui::Button("Find Music")) {
        }

        if (ImGui::Button("Edit Item")) {
        }

        if (ImGui::Button("Remove Item")) {
        }

        if (ImGui::Button("Create Order")) {
        }

        if (ImGui::Button("Sold Items")) {
        }

        ImGui::End();
    }
};
