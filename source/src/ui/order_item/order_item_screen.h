#pragma once
#include "../../music_store/music_repository.h"
#include "../core/screen.h"


class OrderItemScreen : public Screen {
    VoidCallback onOrderItemSuccess;
    MusicRepository *music_repository;
    std::string item_id;

public:
    OrderItemScreen(const std::string &item_id, MusicRepository *music_repository,
                    const VoidCallback &onOrderItemSuccess);

    void drawMainWindows() override;
};
