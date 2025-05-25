#include "show_all_items_screen.h"

#include "imgui.h"

// External variables declared in main.cpp
extern MusicRepository* music_repository;

struct MusicItem {
    std::string id;
    std::string category;
    std::string type;
    std::string name;
    std::string artist;
    std::string price;
    std::string quantity;
};

void ShowAllItemsScreen::render() {
    static std::vector<MusicItem> items;
    static bool loading = true;
    static bool error = false;
    static std::string error_message;
    static bool mysql_available = true;

    // Center the window
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f),
                           ImGuiCond_FirstUseEver, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);

    ImGui::Begin("Show All Items", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Text("Music Inventory");
    ImGui::Separator();

    // Check if music repository is available
    if (music_repository == nullptr) {
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Database not connected!");
        if (ImGui::Button("Connect to Database", ImVec2(180, 30))) {
            // Logic to navigate to connect screen would go here
        }
        ImGui::End();
        return;
    }

    // Fetch items when loading
    if (loading && mysql_available) {
        items.clear();
        error = false;

        // try {
        //     // Try to fetch data from the database
        //     if (music_repository->conn) {
        //         int qstate = mysql_query(music_repository->conn, "SELECT * FROM musicinfo_tb");
        //
        //         if (!qstate) {
        //             MYSQL_RES* res = mysql_store_result(music_repository->conn);
        //             MYSQL_ROW row;
        //
        //             while ((row = mysql_fetch_row(res))) {
        //                 MusicItem item;
        //                 item.id = row[0] ? row[0] : "";
        //                 item.category = row[1] ? row[1] : "";
        //                 item.type = row[2] ? row[2] : "";
        //                 item.name = row[3] ? row[3] : "";
        //                 item.artist = row[4] ? row[4] : "";
        //                 item.price = row[5] ? row[5] : "";
        //                 item.quantity = row[6] ? row[6] : "";
        //                 items.push_back(item);
        //             }
        //
        //             mysql_free_result(res);
        //         } else {
        //             error = true;
        //             error_message = "Query execution problem: ";
        //             error_message += mysql_error(music_repository->conn);
        //         }
        //     } else {
        //         error = true;
        //         error_message = "Database connection not established";
        //     }
        // } catch (const std::exception& e) {
        //     error = true;
        //     error_message = "Error loading data: ";
        //     error_message += e.what();
        // }

        loading = false;
    }

    if (error) {
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "%s", error_message.c_str());

        if (ImGui::Button("Retry", ImVec2(120, 30))) {
            loading = true;
        }
    } else {
        // Display table of items
        if (ImGui::BeginTable("items_table", 7, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY)) {
            // Setup headers
            ImGui::TableSetupColumn("ID");
            ImGui::TableSetupColumn("Category");
            ImGui::TableSetupColumn("Type");
            ImGui::TableSetupColumn("Name");
            ImGui::TableSetupColumn("Artist");
            ImGui::TableSetupColumn("Price");
            ImGui::TableSetupColumn("Quantity");
            ImGui::TableHeadersRow();

            // Display rows
            for (const auto& item : items) {
                ImGui::TableNextRow();

                ImGui::TableNextColumn();
                ImGui::Text("%s", item.id.c_str());

                ImGui::TableNextColumn();
                ImGui::Text("%s", item.category.c_str());

                ImGui::TableNextColumn();
                ImGui::Text("%s", item.type.c_str());

                ImGui::TableNextColumn();
                ImGui::Text("%s", item.name.c_str());

                ImGui::TableNextColumn();
                ImGui::Text("%s", item.artist.c_str());

                ImGui::TableNextColumn();
                ImGui::Text("%s", item.price.c_str());

                ImGui::TableNextColumn();
                ImGui::Text("%s", item.quantity.c_str());
            }

            ImGui::EndTable();
        }

        // Refresh button
        if (ImGui::Button("Refresh", ImVec2(120, 30))) {
            loading = true;
        }
    }

    ImGui::End();
}