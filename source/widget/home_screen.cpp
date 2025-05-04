#include "home_screen.h"

Button HomeScreen::menuItems[] = {
    Button(200, 50, "Create Order"),
    Button(200, 50, "Find Music"),
    Button(200, 50, "Sold Items"),
    Button(200, 50, "Item in Stock"),
    Button(200, 50, "All Items"),
    Button(200, 50, "Add New Item"),
    Button(200, 50, "Edit Item"),
    Button(200, 50, "Remove Item"),
    Button(200, 50, "Exit")};

void HomeScreen::display(HDC hdc) const
{
    for (const auto& item : menuItems) {
        item.display(hdc);
    }
}