#pragma once
#include <functional>

using VoidCallback = std::function<void()>;

class Screen {
public:
    virtual ~Screen() = default;

    virtual void render() = 0;

    virtual void onShow() {
    }

    virtual void onHide() {
    }
};
