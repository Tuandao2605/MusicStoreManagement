

#include "order_item_screen.h"
#include "imgui.h"


OrderItemScreen::OrderItemScreen(const std::string &item_id, MusicRepository *music_repository,
                                 const VoidCallback &onOrderItemSuccess) : Screen("Create Order Item"),
                                                                           onOrderItemSuccess(onOrderItemSuccess),
                                                                           music_repository(music_repository),
                                                                           item_id(item_id) {
    auto item_opt = music_repository->getItemById(item_id);
    if (item_opt.has_value()) {
        const auto &item = item_opt.value();
        state.price = item.price;
        state.name = item.name;
        state.artist = item.artist;
        // Bạn có thể thêm: state.category = item.category; v.v.
    } else {
        std::cerr << "not found with ID: " << item_id << std::endl;
    }
}

void OrderItemScreen::drawMainWindows() {
    if (ImGui::Button("Back", ImVec2(60, 25))) {
        if (onOrderItemSuccess) {
            onOrderItemSuccess();
        }
    }

    ImGui::SameLine();
    ImGui::Text("Do you want to purchase this item?");

    ImGui::SameLine();
    if (ImGui::Button("Yes")) {
        state.ordered = true;
    }

    ImGui::Separator();
    ImGui::Text("Order Information:");
    ImGui::Text("Item ID: %s", item_id.c_str());
    ImGui::Text("Purchase Price: %.2f", state.price);

    // If the item has already been purchased
    if (state.ordered) {
        ImGui::Separator();
        ImGui::TextColored(ImVec4(0, 1, 0, 1), "Purchase successful at price %.2f", state.price);
        return;
    }
}
