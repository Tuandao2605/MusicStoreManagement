#pragma once
#include "../music_store/music_repository.h"
#include "../ui/core/screen.h"


class ShowAllItemsScreen final : public Screen {
    MusicRepository *music_repository;

public:
    explicit ShowAllItemsScreen(MusicRepository *repository = nullptr)
        : music_repository(repository) {
    }

    void render() override;
};
