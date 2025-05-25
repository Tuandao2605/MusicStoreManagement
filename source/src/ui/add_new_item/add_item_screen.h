#pragma once
#include <string>

#include "../../music_store/music_repository.h"
#include "../core/screen.h"

class AddItemScreen final : public Screen {
    std::string category = "";
    std::string type = "";
    std::string name = "";
    std::string artist = "";
    float price = 0.0;
    int quantity = 0;
    MusicRepository *music_repository;

public:
    explicit AddItemScreen(MusicRepository *music_repository)
        : music_repository(music_repository) {
    }

    void render() override;
};
