// item_in_stock_screen.h
#pragma once
#include "../music_store/music_repository.h"
#include "../ui/core/screen.h"

class item_in_stock_screen final : public Screen {
private:
    MusicRepository* music_repository;

public:
    explicit item_in_stock_screen(MusicRepository* repository = nullptr)
        : music_repository(repository) {}

    void render() override;
};