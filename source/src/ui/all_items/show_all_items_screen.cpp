#include "show_all_items_screen.h"

#include <map>
#include <ranges>

#include "imgui.h"

void ShowAllItemsScreen::render() {
    static std::vector<MusicItem> items;
    static bool loading = true;
    static bool error = false;
    static std::string error_message;
    static bool mysql_available = true;
    static std::string editing_id;
    static std::map<std::string, MusicItem> modified_items;
    static bool save_success = false;
    static float message_timer = 0.0f;
    static bool adding_new_item = false;

    // For editing and adding new items
    static char category_buf[128] = "";
    static char type_buf[128] = "";
    static char name_buf[128] = "";
    static char artist_buf[128] = "";
    static char price_buf[32] = "";
    static char quantity_buf[32] = "";

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

        try {
            items = music_repository->GetAllItems();
        } catch (const std::exception &e) {
            error = true;
            error_message = "Error loading data: ";
            error_message += e.what();
        }

        loading = false;
    }

    if (error) {
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "%s", error_message.c_str());

        if (ImGui::Button("Retry", ImVec2(120, 30))) {
            loading = true;
        }
    } else {
        // Show success message with timer
        if (save_success) {
            ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Changes saved successfully!");
            message_timer += ImGui::GetIO().DeltaTime;
            if (message_timer > 3.0f) {
                save_success = false;
                message_timer = 0.0f;
            }
        }

        // Display modified items count
        if (!modified_items.empty()) {
            ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.0f, 1.0f),
                               "%zu item(s) modified and not yet saved", modified_items.size());
        }

        // Add new item form
        if (adding_new_item) {
            ImGui::BeginChild("AddNewItemForm", ImVec2(0, 200), true);
            ImGui::Text("Add New Item");

            ImGui::Text("Category:");
            ImGui::SameLine(100);
            ImGui::SetNextItemWidth(200);
            ImGui::InputText("##new_category", category_buf, IM_ARRAYSIZE(category_buf));

            ImGui::Text("Type:");
            ImGui::SameLine(100);
            ImGui::SetNextItemWidth(200);
            ImGui::InputText("##new_type", type_buf, IM_ARRAYSIZE(type_buf));

            ImGui::Text("Name:");
            ImGui::SameLine(100);
            ImGui::SetNextItemWidth(200);
            ImGui::InputText("##new_name", name_buf, IM_ARRAYSIZE(name_buf));

            ImGui::Text("Artist:");
            ImGui::SameLine(100);
            ImGui::SetNextItemWidth(200);
            ImGui::InputText("##new_artist", artist_buf, IM_ARRAYSIZE(artist_buf));

            ImGui::Text("Price:");
            ImGui::SameLine(100);
            ImGui::SetNextItemWidth(200);
            ImGui::InputText("##new_price", price_buf, IM_ARRAYSIZE(price_buf));

            ImGui::Text("Quantity:");
            ImGui::SameLine(100);
            ImGui::SetNextItemWidth(200);
            ImGui::InputText("##new_quantity", quantity_buf, IM_ARRAYSIZE(quantity_buf));

            ImGui::Separator();

            if (ImGui::Button("Save New Item", ImVec2(120, 30))) {
                // Validate inputs
                bool valid_inputs = true;
                std::string validation_error;

                if (strlen(category_buf) == 0 || strlen(type_buf) == 0 ||
                    strlen(name_buf) == 0 || strlen(artist_buf) == 0) {
                    valid_inputs = false;
                    validation_error = "All text fields must be filled";
                }

                float price = 0.0f;
                int quantity = 0;

                try {
                    if (strlen(price_buf) > 0) {
                        price = std::stof(price_buf);
                    } else {
                        valid_inputs = false;
                        validation_error = "Price is required";
                    }

                    if (strlen(quantity_buf) > 0) {
                        quantity = std::stoi(quantity_buf);
                    } else {
                        valid_inputs = false;
                        validation_error = "Quantity is required";
                    }
                } catch ([[maybe_unused]] const std::exception &e) {
                    valid_inputs = false;
                    validation_error = "Invalid price or quantity value";
                }

                if (valid_inputs) {
                    try {
                        MusicItem new_item;
                        new_item.category = category_buf;
                        new_item.type = type_buf;
                        new_item.name = name_buf;
                        new_item.artist = artist_buf;
                        new_item.price = price;
                        new_item.quantity = quantity;

                        music_repository->AddItem(new_item);

                        // Clear form and exit add mode
                        category_buf[0] = '\0';
                        type_buf[0] = '\0';
                        name_buf[0] = '\0';
                        artist_buf[0] = '\0';
                        price_buf[0] = '\0';
                        quantity_buf[0] = '\0';
                        adding_new_item = false;

                        // Refresh the list
                        loading = true;
                        save_success = true;
                        message_timer = 0.0f;
                    } catch (const std::exception &e) {
                        error = true;
                        error_message = "Error adding item: ";
                        error_message += e.what();
                    }
                } else {
                    ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "%s", validation_error.c_str());
                }
            }

            ImGui::SameLine();
            if (ImGui::Button("Cancel", ImVec2(120, 30))) {
                adding_new_item = false;
                category_buf[0] = '\0';
                type_buf[0] = '\0';
                name_buf[0] = '\0';
                artist_buf[0] = '\0';
                price_buf[0] = '\0';
                quantity_buf[0] = '\0';
            }

            ImGui::EndChild();
        }

        // Display table of items
        if (ImGui::BeginTable("items_table", 8,
                              ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY)) {
            // Setup headers
            ImGui::TableSetupColumn("ID");
            ImGui::TableSetupColumn("Category");
            ImGui::TableSetupColumn("Type");
            ImGui::TableSetupColumn("Name");
            ImGui::TableSetupColumn("Artist");
            ImGui::TableSetupColumn("Price");
            ImGui::TableSetupColumn("Quantity");
            ImGui::TableSetupColumn("Actions");
            ImGui::TableHeadersRow();

            // Display rows
            for (const auto &item: items) {
                ImGui::TableNextRow();
                ImGui::PushID(item.id.c_str());

                ImGui::TableNextColumn();
                ImGui::Text("%s", item.id.c_str());

                // Check if this row is being edited
                const bool is_editing = (editing_id == item.id);

                // Use modified value if available
                const MusicItem &display_item = modified_items.contains(item.id) ? modified_items[item.id] : item;

                // Category
                ImGui::TableNextColumn();
                if (is_editing) {
                    ImGui::SetNextItemWidth(-1);
                    ImGui::InputText("##category", category_buf, IM_ARRAYSIZE(category_buf));
                } else {
                    ImGui::Text("%s", display_item.category.c_str());
                }

                // Type
                ImGui::TableNextColumn();
                if (is_editing) {
                    ImGui::SetNextItemWidth(-1);
                    ImGui::InputText("##type", type_buf, IM_ARRAYSIZE(type_buf));
                } else {
                    ImGui::Text("%s", display_item.type.c_str());
                }

                // Name
                ImGui::TableNextColumn();
                if (is_editing) {
                    ImGui::SetNextItemWidth(-1);
                    ImGui::InputText("##name", name_buf, IM_ARRAYSIZE(name_buf));
                } else {
                    ImGui::Text("%s", display_item.name.c_str());
                }

                // Artist
                ImGui::TableNextColumn();
                if (is_editing) {
                    ImGui::SetNextItemWidth(-1);
                    ImGui::InputText("##artist", artist_buf, IM_ARRAYSIZE(artist_buf));
                } else {
                    ImGui::Text("%s", display_item.artist.c_str());
                }

                // Price
                ImGui::TableNextColumn();
                if (is_editing) {
                    ImGui::SetNextItemWidth(-1);
                    ImGui::InputText("##price", price_buf, IM_ARRAYSIZE(price_buf));
                } else {
                    ImGui::Text("%.2f", display_item.price);
                }

                // Quantity
                ImGui::TableNextColumn();
                if (is_editing) {
                    ImGui::SetNextItemWidth(-1);
                    ImGui::InputText("##quantity", quantity_buf, IM_ARRAYSIZE(quantity_buf));
                } else {
                    ImGui::Text("%d", display_item.quantity);
                }

                // Action buttons
                ImGui::TableNextColumn();
                if (is_editing) {
                    if (ImGui::Button("Save")) {
                        // Create updated item
                        MusicItem updated = item;
                        updated.category = category_buf;
                        updated.type = type_buf;
                        updated.name = name_buf;
                        updated.artist = artist_buf;
                        updated.price = std::stof(price_buf);
                        updated.quantity = std::stoi(quantity_buf);

                        // Add to modified items
                        modified_items[item.id] = updated;
                        editing_id = "";
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Cancel")) {
                        editing_id = "";
                    }
                } else {
                    if (ImGui::Button("Edit")) {
                        editing_id = item.id;

                        // Initialize edit buffers with current values (use either modified or original)
                        strncpy(category_buf, display_item.category.c_str(), sizeof(category_buf) - 1);
                        strncpy(type_buf, display_item.type.c_str(), sizeof(type_buf) - 1);
                        strncpy(name_buf, display_item.name.c_str(), sizeof(name_buf) - 1);
                        strncpy(artist_buf, display_item.artist.c_str(), sizeof(artist_buf) - 1);
                        snprintf(price_buf, sizeof(price_buf), "%.2f", display_item.price);
                        snprintf(quantity_buf, sizeof(quantity_buf), "%d", display_item.quantity);
                    }
                }
                ImGui::PopID();
            }
            ImGui::EndTable();
        }

        // Action buttons
        if (ImGui::Button("Refresh", ImVec2(120, 30))) {
            loading = true;
        }

        ImGui::SameLine();

        // Add Item button
        if (ImGui::Button("Add Item", ImVec2(180, 30))) {
            // Ensure we're not in edit mode when adding
            if (editing_id.empty()) {
                adding_new_item = !adding_new_item;

                // Clear form fields when opening the form
                if (adding_new_item) {
                    category_buf[0] = '\0';
                    type_buf[0] = '\0';
                    name_buf[0] = '\0';
                    artist_buf[0] = '\0';
                    price_buf[0] = '\0';
                    quantity_buf[0] = '\0';
                }
            }
        }

        if (!modified_items.empty()) {
            ImGui::SameLine();
            if (ImGui::Button("Save All Changes", ImVec2(180, 30))) {
                error = false;
                try {
                    // Update each modified item in database
                    for (const auto &updated_item: modified_items | views::values) {
                        music_repository->UpdateItem(updated_item);
                    }

                    // Clear modified items
                    modified_items.clear();
                    save_success = true;
                    message_timer = 0.0f;

                    // Refresh the list
                    loading = true;
                } catch (const std::exception &e) {
                    error = true;
                    error_message = "Error saving changes: ";
                    error_message += e.what();
                }
            }

            ImGui::SameLine();
            if (ImGui::Button("Discard Changes", ImVec2(180, 30))) {
                modified_items.clear();
                editing_id = "";
                loading = true;
            }
        }
    }

    ImGui::End();
}
