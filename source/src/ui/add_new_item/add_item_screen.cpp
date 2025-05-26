#include "add_item_screen.h"
#include "imgui.h"
#include <string>


void AddItemScreen::drawMainWindows() {
    // Character buffers for text input
    static char category_buf[128] = "";
    static char type_buf[128] = "";
    static char name_buf[128] = "";
    static char artist_buf[128] = "";
    static char price_buf[32] = "0.0";
    static char quantity_buf[32] = "0";
    static bool error_occurred = false;
    static std::string error_message = "";
    static bool success = false;

    ImGui::Begin("Add New Music Item", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Text("Enter Music Item Details");
    ImGui::Separator();

    ImGui::InputText("Category", category_buf, sizeof(category_buf));
    ImGui::InputText("Type", type_buf, sizeof(type_buf));
    ImGui::InputText("Name", name_buf, sizeof(name_buf));
    ImGui::InputText("Artist", artist_buf, sizeof(artist_buf));
    ImGui::InputText("Price", price_buf, sizeof(price_buf), ImGuiInputTextFlags_CharsDecimal);
    ImGui::InputText("Quantity", quantity_buf, sizeof(quantity_buf), ImGuiInputTextFlags_CharsDecimal);

    ImGui::Separator();

    if (error_occurred) {
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "%s", error_message.c_str());
    }

    if (success) {
        ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Item added successfully!");
    }

    if (ImGui::Button("Add Item", ImVec2(120, 30))) {
        // Validate inputs
        if (category_buf[0] && type_buf[0] && name_buf[0] && artist_buf[0]) {
            try {
                // Convert numeric inputs
                float price_val = std::stof(price_buf);
                int quantity_val = std::stoi(quantity_buf);

                if (price_val >= 0 && quantity_val >= 0) {
                    // Save to member variables
                    category = category_buf;
                    type = type_buf;
                    name = name_buf;
                    artist = artist_buf;
                    price = price_val;
                    quantity = quantity_val;

                    if (music_repository) {
                        const bool result = music_repository->AddNewItemInDatabase(
                            category, type, name, artist, price, quantity);
                        if (result) {
                            success = true;
                            error_occurred = false;
                            // Reset input fields
                            category_buf[0] = '\0';
                            type_buf[0] = '\0';
                            name_buf[0] = '\0';
                            artist_buf[0] = '\0';
                            strcpy(price_buf, "0.0");
                            strcpy(quantity_buf, "0");
                        } else {
                            error_occurred = true;
                            error_message = "Failed to add item to database";
                            success = false;
                        }
                    }
                } else {
                    error_occurred = true;
                    error_message = "Price and quantity cannot be negative";
                    success = false;
                }
            } catch ([[maybe_unused]] const std::exception &e) {
                error_occurred = true;
                error_message = "Invalid numeric input";
                success = false;
            }
        } else {
            error_occurred = true;
            error_message = "All fields are required";
            success = false;
        }
    }

    ImGui::SameLine();
    if (ImGui::Button("Clear", ImVec2(120, 30))) {
        category_buf[0] = '\0';
        type_buf[0] = '\0';
        name_buf[0] = '\0';
        artist_buf[0] = '\0';
        strcpy(price_buf, "0.0");
        strcpy(quantity_buf, "0");
        error_occurred = false;
        success = false;
    }
}
