#pragma once
#include "../../music_store/music_repository.h"
#include "../core/screen.h"

class item_in_stock_screen final : public Screen {
    MusicRepository *music_repository;
    VoidCallback back_callback;

public:
    explicit item_in_stock_screen(MusicRepository *repository,const VoidCallback& back_callback)
        : music_repository(repository), back_callback(back_callback) {
    }

    void drawMainWindows() override;
};
