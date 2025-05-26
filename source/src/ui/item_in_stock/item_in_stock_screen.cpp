// item_in_stock_screen.cpp
#include "item_in_stock_screen.h"
#include "imgui.h"

void item_in_stock_screen::drawMainWindows() {
    static std::vector<MusicItem> filtered_items;
    static bool show_items = false;

    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f),
                           ImGuiCond_FirstUseEver, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize(ImVec2(700, 500), ImGuiCond_FirstUseEver);

    ImGui::Begin("Items In Stock", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    // Add Back button at the top
    if (ImGui::Button("Back", ImVec2(60, 25))) {
        if (back_callback) back_callback();
    }

    ImGui::Text("Items Currently In Stock");
    ImGui::Separator();

    if (music_repository == nullptr) {
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Database not connected!");
        return;
    }

    static int min_quantity = 1;
    ImGui::InputInt("Minimum Quantity", &min_quantity);



    if (ImGui::Button("Show In-Stock Items", ImVec2(150, 30))) {
        // This would call music_repository->ItemInStock() with parameters
        // Since we need to use ImGui for display, we'd need to modify the
        // repository method to return data instead of directly outputting it
        if (music_repository) {
            filtered_items = music_repository->getItemsInStock(min_quantity); // This function needs to be implemented in MusicRepository
            show_items = true;
        }
    }

    // Display results in a table
    if (show_items) {
        if (ImGui::BeginTable("InStockTable", 7, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
            ImGui::TableSetupColumn("ID");
            ImGui::TableSetupColumn("Category");
            ImGui::TableSetupColumn("Type");
            ImGui::TableSetupColumn("Name");
            ImGui::TableSetupColumn("Artist");
            ImGui::TableSetupColumn("Price");
            ImGui::TableSetupColumn("Quantity");
            ImGui::TableHeadersRow();

            for (const auto& item : filtered_items) {
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0); ImGui::Text("%s", item.id.c_str());
                ImGui::TableSetColumnIndex(1); ImGui::Text("%s", item.category.c_str());
                ImGui::TableSetColumnIndex(2); ImGui::Text("%s", item.type.c_str());
                ImGui::TableSetColumnIndex(3); ImGui::Text("%s", item.name.c_str());
                ImGui::TableSetColumnIndex(4); ImGui::Text("%s", item.artist.c_str());
                ImGui::TableSetColumnIndex(5); ImGui::Text("%.2f", item.price);
                ImGui::TableSetColumnIndex(6); ImGui::Text("%d", item.quantity);
            }

            ImGui::EndTable();
        }
    }
}