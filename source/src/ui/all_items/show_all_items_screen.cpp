#include "show_all_items_screen.h"

#include <map>
#include <ranges>

#include "imgui.h"

void ShowAllItemsScreen::render() {
    ImGui::Text("Show All Music Items");

    if (state.loading) {
        reload();
        state.loading = false;
    }

    if (!state.error_message.empty()) {
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "Error: %s", state.error_message.c_str());
    }

    if (!state.success_message.empty()) {
        ImGui::TextColored(ImVec4(0, 1, 0, 1), "%s", state.success_message.c_str());
    }

    // Filter section
    ImGui::Separator();
    ImGui::Text("Filter Items");

    // Create local storage for filter values
    static std::array<char, 128> filter_category = {};
    static std::array<char, 128> filter_type = {};
    static std::array<char, 128> filter_name = {};
    static std::array<char, 128> filter_artist = {};
    static std::array<char, 128> filter_min_price = {};
    static std::array<char, 128> filter_max_price = {};
    static std::array<char, 128> filter_min_quantity = {};
    static std::array<char, 128> filter_max_quantity = {};

    // Filter inputs
    if (ImGui::BeginTable("filter_table", 4, ImGuiTableFlags_Borders)) {
        ImGui::TableNextRow();

        ImGui::TableSetColumnIndex(0);
        ImGui::Text("Category");
        ImGui::TableSetColumnIndex(1);
        ImGui::InputText("##filter_category", filter_category.data(), filter_category.size());

        ImGui::TableSetColumnIndex(2);
        ImGui::Text("Type");
        ImGui::TableSetColumnIndex(3);
        ImGui::InputText("##filter_type", filter_type.data(), filter_type.size());

        ImGui::TableNextRow();

        ImGui::TableSetColumnIndex(0);
        ImGui::Text("Name");
        ImGui::TableSetColumnIndex(1);
        ImGui::InputText("##filter_name", filter_name.data(), filter_name.size());

        ImGui::TableSetColumnIndex(2);
        ImGui::Text("Artist");
        ImGui::TableSetColumnIndex(3);
        ImGui::InputText("##filter_artist", filter_artist.data(), filter_artist.size());

        ImGui::TableNextRow();

        ImGui::TableSetColumnIndex(0);
        ImGui::Text("Min Price");
        ImGui::TableSetColumnIndex(1);
        ImGui::InputText("##filter_min_price", filter_min_price.data(), filter_min_price.size());

        ImGui::TableSetColumnIndex(2);
        ImGui::Text("Max Price");
        ImGui::TableSetColumnIndex(3);
        ImGui::InputText("##filter_max_price", filter_max_price.data(), filter_max_price.size());

        ImGui::TableNextRow();

        ImGui::TableSetColumnIndex(0);
        ImGui::Text("Min Quantity");
        ImGui::TableSetColumnIndex(1);
        ImGui::InputText("##filter_min_quantity", filter_min_quantity.data(), filter_min_quantity.size());

        ImGui::TableSetColumnIndex(2);
        ImGui::Text("Max Quantity");
        ImGui::TableSetColumnIndex(3);
        ImGui::InputText("##filter_max_quantity", filter_max_quantity.data(), filter_max_quantity.size());

        ImGui::EndTable();
    }

    if (ImGui::Button("Apply Filter")) {
        // Clear previous filter state
        state.filter_state = FilterState();

        // Set new filter values
        static std::string category_str, type_str, name_str, artist_str;
        static float min_price_val, max_price_val;
        static int min_quantity_val, max_quantity_val;

        if (strlen(filter_category.data()) > 0) {
            category_str = filter_category.data();
            state.filter_state.category = &category_str;
        }

        if (strlen(filter_type.data()) > 0) {
            type_str = filter_type.data();
            state.filter_state.type = &type_str;
        }

        if (strlen(filter_name.data()) > 0) {
            name_str = filter_name.data();
            state.filter_state.name = &name_str;
        }

        if (strlen(filter_artist.data()) > 0) {
            artist_str = filter_artist.data();
            state.filter_state.artist = &artist_str;
        }

        if (strlen(filter_min_price.data()) > 0 && IsValidFloat(filter_min_price.data(), min_price_val)) {
            state.filter_state.min_price = &min_price_val;
        }

        if (strlen(filter_max_price.data()) > 0 && IsValidFloat(filter_max_price.data(), max_price_val)) {
            state.filter_state.max_price = &max_price_val;
        }

        if (strlen(filter_min_quantity.data()) > 0 && IsValidInt(filter_min_quantity.data(), min_quantity_val)) {
            state.filter_state.min_quantity = &min_quantity_val;
        }

        if (strlen(filter_max_quantity.data()) > 0 && IsValidInt(filter_max_quantity.data(), max_quantity_val)) {
            state.filter_state.max_quantity = &max_quantity_val;
        }

        filter_item();
    }

    ImGui::SameLine();
    if (ImGui::Button("Clear Filter")) {
        state.filter_state = FilterState();
        memset(filter_category.data(), 0, filter_category.size());
        memset(filter_type.data(), 0, filter_type.size());
        memset(filter_name.data(), 0, filter_name.size());
        memset(filter_artist.data(), 0, filter_artist.size());
        memset(filter_min_price.data(), 0, filter_min_price.size());
        memset(filter_max_price.data(), 0, filter_max_price.size());
        memset(filter_min_quantity.data(), 0, filter_min_quantity.size());
        memset(filter_max_quantity.data(), 0, filter_max_quantity.size());
        filter_item();
    }

    ImGui::Text("Showing %zu items (filtered from %zu total)",
                state.filtered_items.size(), state.items.size());
    ImGui::Separator();

    // Giới hạn chiều cao bảng, ví dụ 300.0f pixel
    if (ImGui::BeginChild("items_table_container", ImVec2(0, 300.0f), true)) {
        if (ImGui::BeginTable("items_table", 8, ImGuiTableFlags_Borders | ImGuiTableFlags_ScrollY)) {
            ImGui::TableSetupScrollFreeze(0, 1);
            ImGui::TableSetupColumn("ID");
            ImGui::TableSetupColumn("Category");
            ImGui::TableSetupColumn("Type");
            ImGui::TableSetupColumn("Name");
            ImGui::TableSetupColumn("Artist");
            ImGui::TableSetupColumn("Price");
            ImGui::TableSetupColumn("Quantity");
            ImGui::TableSetupColumn("Actions");
            ImGui::TableHeadersRow();

            // Show filtered items instead of all items
            for (auto &item: state.filtered_items) {
                ImGui::TableNextRow();

                if (state.editing_id == item.id) {
                    ImGui::TableSetColumnIndex(0);
                    ImGui::Text("%s", item.id.c_str());

                    ImGui::TableSetColumnIndex(1);
                    ImGui::InputText(("##edit_category_" + item.id).c_str(), state.edit_category[item.id].data(), 128);

                    ImGui::TableSetColumnIndex(2);
                    ImGui::InputText(("##edit_type_" + item.id).c_str(), state.edit_type[item.id].data(), 128);

                    ImGui::TableSetColumnIndex(3);
                    ImGui::InputText(("##edit_name_" + item.id).c_str(), state.edit_name[item.id].data(), 128);

                    ImGui::TableSetColumnIndex(4);
                    ImGui::InputText(("##edit_artist_" + item.id).c_str(), state.edit_artist[item.id].data(), 128);

                    ImGui::TableSetColumnIndex(5);
                    ImGui::InputText(("##edit_price_" + item.id).c_str(), state.edit_price[item.id].data(), 128);

                    ImGui::TableSetColumnIndex(6);
                    ImGui::InputText(("##edit_quantity_" + item.id).c_str(), state.edit_quantity[item.id].data(), 128);

                    ImGui::TableSetColumnIndex(7);
                    if (ImGui::Button(("Save##" + item.id).c_str())) {
                        float price;
                        int quantity;
                        if (!IsValidFloat(state.edit_price[item.id].data(), price) || !IsValidInt(
                                state.edit_quantity[item.id].data(), quantity)) {
                            state.error_message = "Invalid number format.";
                            continue;
                        }

                        MusicItem updated = item;
                        updated.name = state.edit_name[item.id].data();
                        updated.category = state.edit_category[item.id].data();
                        updated.type = state.edit_type[item.id].data();
                        updated.artist = state.edit_artist[item.id].data();
                        updated.price = price;
                        updated.quantity = quantity;

                        music_repository->UpdateItem(updated);
                        reload();
                        state.editing_id = "";
                    }

                    ImGui::SameLine();
                    if (ImGui::Button(("Cancel##" + item.id).c_str())) {
                        state.editing_id = "";
                    }
                } else {
                    ImGui::TableSetColumnIndex(0);
                    ImGui::Text("%s", item.id.c_str());
                    ImGui::TableSetColumnIndex(1);
                    ImGui::Text("%s", item.category.c_str());
                    ImGui::TableSetColumnIndex(2);
                    ImGui::Text("%s", item.type.c_str());
                    ImGui::TableSetColumnIndex(3);
                    ImGui::Text("%s", item.name.c_str());
                    ImGui::TableSetColumnIndex(4);
                    ImGui::Text("%s", item.artist.c_str());
                    ImGui::TableSetColumnIndex(5);
                    ImGui::Text("%.2f", item.price);
                    ImGui::TableSetColumnIndex(6);
                    ImGui::Text("%d", item.quantity);

                    ImGui::TableSetColumnIndex(7);
                    if (ImGui::Button(("Edit##" + item.id).c_str())) {
                        state.editing_id = item.id;
                        strncpy(state.edit_name[item.id].data(), item.name.c_str(), 128);
                        snprintf(state.edit_price[item.id].data(), 128, "%.2f", item.price);
                        snprintf(state.edit_quantity[item.id].data(), 128, "%d", item.quantity);
                        snprintf(state.edit_category[item.id].data(), 128, "%s", item.category.c_str());
                        snprintf(state.edit_type[item.id].data(), 128, "%s", item.type.c_str());
                        snprintf(state.edit_artist[item.id].data(), 128, "%s", item.artist.c_str());
                    }

                    ImGui::SameLine();
                    if (ImGui::Button(("Delete##" + item.id).c_str())) {
                        music_repository->RemoveItem(item.id);
                        reload();
                    }
                }
            }

            ImGui::EndTable();
        }
        ImGui::EndChild();
    }

    if (!state.add_item_error_message.empty()) {
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "Error: %s", state.add_item_error_message.c_str());
    }

    if (!state.add_item_success_message.empty()) {
        ImGui::TextColored(ImVec4(0, 1, 0, 1), "%s", state.add_item_success_message.c_str());
    }
    ImGui::Separator();
    ImGui::Text("Add New Item");

    ImGui::InputText("Category", state.new_category.data(), 128);
    ImGui::InputText("Type", state.new_type.data(), 128);
    ImGui::InputText("Name", state.new_name.data(), 128);
    ImGui::InputText("Artist", state.new_artist.data(), 128);
    ImGui::InputText("Price", state.new_price.data(), 128);
    ImGui::InputText("Quantity", state.new_quantity.data(), 128);

    if (ImGui::Button("Add Item")) {
        int quantity;

        if (float price; !IsValidFloat(state.new_price.data(), price) || !IsValidInt(
                             state.new_quantity.data(), quantity)) {
            state.add_item_error_message = "Invalid number format.";
        } else {
            const MusicItem item{
                .category = state.new_category.data(),
                .type = state.new_type.data(),
                .name = state.new_name.data(),
                .artist = state.new_artist.data(),
                .price = price,
                .quantity = quantity
            };

            music_repository->AddItem(item);
            reload();
        }
    }
}
