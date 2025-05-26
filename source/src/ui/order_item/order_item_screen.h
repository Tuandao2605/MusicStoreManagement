#pragma once
#include "../../music_store/music_repository.h"
#include "../core/screen.h"

struct OrderState {
    bool ordered = false;
    float price = 0.0f;
    std::string name;
    std::string artist;
    std::string category;
};

class OrderItemScreen : public Screen {
private:
    VoidCallback onOrderItemSuccess;
    MusicRepository *music_repository;
    std::string item_id;
    OrderState state;
public:
    OrderItemScreen(const std::string &item_id, MusicRepository *music_repository,
                    const VoidCallback &onOrderItemSuccess);

    void drawMainWindows() override;
};
