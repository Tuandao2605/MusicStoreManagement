// item_in_stock_screen.h
#pragma once
#include "../music_store/music_repository.h"
#include "../ui/core/screen.h"

class ItemInStockScreen final : public Screen {
private:
    MusicRepository* music_repository;

public:
    explicit ItemInStockScreen(MusicRepository* repository = nullptr)
        : music_repository(repository) {}

    void render() override;
};