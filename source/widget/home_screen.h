#pragma once

#include <iostream>
#include "button.h"

class HomeScreen : public Widget
{
private:
    static const int menuItemCount = 9; // Number of menu items
    static Button menuItems[];

    int currentIndex = 0; // Current selected index
    int offset_x = 50; // Default offset for menu items

public:
    HomeScreen(int width, int height) : Widget(width, height) {
        for (int i = 0; i < menuItemCount; ++i) {
            menuItems[i].setOffsetX(offset_x);
            menuItems[i].setOffsetY(i * height / menuItemCount);
        }

        menuItems[0].setSelected(true); // Set the first item as selected by default
    }
    void display(HDC hdc) const override;

    void selectItem(int index) {
        if (index < 0 || index >= menuItemCount) {
            std::cerr << "Index out of bounds" << std::endl;
            return;
        }
        
        currentIndex = index;
        for (int i = 0; i < menuItemCount; ++i) {
            menuItems[i].setSelected(i == currentIndex);
        }
    }

    int getCurrentIndex() const {
        return currentIndex;
    }

    void nextItem() {
        currentIndex = (currentIndex + 1) % menuItemCount;
        selectItem(currentIndex);
    }

    void previousItem() {
        currentIndex = (currentIndex - 1 + menuItemCount) % menuItemCount;
        selectItem(currentIndex);
    }
};
