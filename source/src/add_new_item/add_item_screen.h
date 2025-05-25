#pragma once
#include <string>

#include "../ui/core/screen.h"

class AddItemScreen final : public Screen {
private:
    std::string category = "";
    std::string type = "";
    std::string name = "";
    std::string artist = "";
    float price = 0.0;
    int quantity = 0;

public:
    AddItemScreen() = default;

    void render() override;
};
