#include "find_music_screen.h"

#include "imgui.h"

void FindMusicScreen::drawMainWindows() {
    // Character buffers for text input
    static char name_buf[128] = "";
    static char category_buf[128] = "";
    static char type_buf[128] = "";
    static char artist_buf[128] = "";
    static bool error_occurred = false;
    static std::string error_message = "";
    static bool search_performed = false;
    static std::vector<MusicItem> search_results;

    ImGui::Begin("Find Music", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    // Add Back button at the top
    if (ImGui::Button("Back", ImVec2(60, 25))) {
        if (back_callback) back_callback();
    }

    ImGui::SameLine();
    ImGui::Text("Search for Music");
    ImGui::Separator();

    // Rest of the render method remains the same
    if (music_repository == nullptr) {
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Database not connected!");
        return;
    }

    // Search criteria inputs
    ImGui::BeginGroup();
    ImGui::Text("Search Criteria (at least one field required)");
    ImGui::InputText("Name", name_buf, sizeof(name_buf));
    ImGui::InputText("Category", category_buf, sizeof(category_buf));
    ImGui::InputText("Type", type_buf, sizeof(type_buf));
    ImGui::InputText("Artist", artist_buf, sizeof(artist_buf));
    ImGui::EndGroup();

    ImGui::Separator();

    if (error_occurred) {
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "%s", error_message.c_str());
    }

    // Search and Clear buttons
    if (ImGui::Button("Search", ImVec2(120, 30))) {
        // Search logic remains the same
        if (name_buf[0] || category_buf[0] || type_buf[0] || artist_buf[0]) {
            try {
                // Get search parameters
                const std::string name = name_buf;
                const std::string category = category_buf;
                const std::string type = type_buf;
                const std::string artist = artist_buf;

                // Call repository method
                search_results = music_repository->FindMusic(name, category, type, artist);
                search_performed = true;
                error_occurred = false;
            } catch (const std::exception& e) {
                error_occurred = true;
                error_message = "Error performing search: ";
                error_message += e.what();
                search_performed = false;
            }
        } else {
            error_occurred = true;
            error_message = "At least one search field is required";
            search_performed = false;
        }
    }

    ImGui::SameLine();
    if (ImGui::Button("Clear", ImVec2(120, 30))) {
        name_buf[0] = '\0';
        category_buf[0] = '\0';
        type_buf[0] = '\0';
        artist_buf[0] = '\0';
        error_occurred = false;
        search_performed = false;
        search_results.clear();
    }

    if (search_performed) {
        ImGui::Separator();
        ImGui::Text("Search Results (%zu items found)", search_results.size());

        if (search_results.empty()) {
            ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.0f, 1.0f), "No matching items found");
        } else {
            // Display results in a table
            if (ImGui::BeginTable("search_results", 7, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY)) {
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
                for (const auto&[id, category, type, name, artist, price, quantity] : search_results) {
                    ImGui::TableNextRow();

                    ImGui::TableNextColumn();
                    ImGui::Text("%s", id.c_str());

                    ImGui::TableNextColumn();
                    ImGui::Text("%s", category.c_str());

                    ImGui::TableNextColumn();
                    ImGui::Text("%s", type.c_str());

                    ImGui::TableNextColumn();
                    ImGui::Text("%s", name.c_str());

                    ImGui::TableNextColumn();
                    ImGui::Text("%s", artist.c_str());

                    ImGui::TableNextColumn();
                    ImGui::Text("%.2f", price);

                    ImGui::TableNextColumn();
                    ImGui::Text("%d", quantity);
                }

                ImGui::EndTable();
            }
        }
    }
}
