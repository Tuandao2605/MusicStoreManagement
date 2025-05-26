#pragma once
#include "../../music_store/music_repository.h"
#include "../core/screen.h"


class ConnectDbScreen final : public Screen {
    MusicRepository *music_repository;
    VoidCallback onConnectDbSuccess;

public:
    explicit ConnectDbScreen(MusicRepository *music_repository, const VoidCallback &onConnectDbSuccess)
        : music_repository(music_repository), onConnectDbSuccess(onConnectDbSuccess) {
    }

    void drawMainWindows() override;
};
