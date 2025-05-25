// item_in_stock_screen.cpp
#include "item_in_stock_screen.h"
#include "imgui.h"
#include <vector>
#include <string>

void item_in_stock_screen::render() {
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f),
                           ImGuiCond_FirstUseEver, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize(ImVec2(700, 500), ImGuiCond_FirstUseEver);

    ImGui::Begin("Items In Stock", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Text("Items Currently In Stock");
    ImGui::Separator();

    if (music_repository == nullptr) {
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Database not connected!");
        ImGui::End();
        return;
    }

    static int min_quantity = 1;
    ImGui::InputInt("Minimum Quantity", &min_quantity);

    if (ImGui::Button("Show In-Stock Items", ImVec2(150, 30))) {
        // This would call music_repository->ItemInStock() with parameters
        // Since we need to use ImGui for display, we'd need to modify the
        // repository method to return data instead of directly outputting it
    }

    // Display results in a table
    if (ImGui::BeginTable("stock_items_table", 7, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY)) {
        // Headers
        ImGui::TableSetupColumn("ID");
        ImGui::TableSetupColumn("Category");
        ImGui::TableSetupColumn("Type");
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("Artist");
        ImGui::TableSetupColumn("Price");
        ImGui::TableSetupColumn("Quantity");
        ImGui::TableHeadersRow();

        // In a real implementation, you would populate the table with data from the repository

        ImGui::EndTable();
    }

    ImGui::End();
}