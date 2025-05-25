#include "find_music_screen.h"

#include "imgui.h"

void FindMusicScreen::render() {
    // Character buffers for text input
    static char name_buf[128] = "";
    static char category_buf[128] = "";
    static char type_buf[128] = "";
    static char artist_buf[128] = "";
    static bool error_occurred = false;
    static std::string error_message = "";
    static bool search_performed = false;
    static std::vector<MusicItem> search_results;

    // Center the window
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f),
                           ImGuiCond_FirstUseEver, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize(ImVec2(700, 500), ImGuiCond_FirstUseEver);

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
        ImGui::End();
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
                std::string name = name_buf;
                std::string category = category_buf;
                std::string type = type_buf;
                std::string artist = artist_buf;

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
                for (const auto& item : search_results) {
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
                    ImGui::Text("%.2f", item.price);

                    ImGui::TableNextColumn();
                    ImGui::Text("%d", item.quantity);
                }

                ImGui::EndTable();
            }
        }
    }

    ImGui::End();
}
