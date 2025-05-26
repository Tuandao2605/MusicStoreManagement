//
// Created by phuc on 26/5/25.
//

#include "order_item_screen.h"


OrderItemScreen::OrderItemScreen(const std::string &item_id, MusicRepository *music_repository,
                                 const VoidCallback &onOrderItemSuccess) : Screen("Create Order Item"),
                                                                           onOrderItemSuccess(onOrderItemSuccess),
                                                                           music_repository(music_repository),
                                                                           item_id(item_id) {
}

void OrderItemScreen::drawMainWindows() {
    if (ImGui::Button("Back"(), ImVec2(60, 25))) {
        if (onOrderItemSuccess) {
            onOrderItemSuccess();
        }
    }
}
