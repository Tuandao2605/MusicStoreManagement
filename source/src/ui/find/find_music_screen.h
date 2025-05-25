#pragma once
#include "../core/screen.h"
#include "../../music_store/music_repository.h"
#include <string>

class FindMusicScreen final : public Screen {
    MusicRepository *music_repository;
    VoidCallback back_callback;

    std::string name;
    std::string category;
    std::string type;
    std::string artist;

public:
    explicit FindMusicScreen(MusicRepository *repository, const VoidCallback &back_callback)
        : music_repository(repository), back_callback(back_callback) {
    }

    void render() override;
};
