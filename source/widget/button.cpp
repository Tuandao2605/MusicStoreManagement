#include "button.h"

void Button::display(HDC hdc) const
{
    // Set colors based on selection state
    COLORREF bgColor = isSelected ? RGB(100, 149, 237) : RGB(240, 240, 240); // CornflowerBlue when selected, light gray when not
    COLORREF textColor = RGB(0, 0, 0); // Black text

    // Create and select a brush for the background
    HBRUSH hBrush = CreateSolidBrush(bgColor);
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

    // Set text color and background mode
    SetTextColor(hdc, textColor);
    SetBkMode(hdc, TRANSPARENT);

    // Draw the rectangle with the background color
    Rectangle(hdc, offset_x, offset_y, offset_x + width, offset_y + height);

    // Calculate text dimensions for centering
    RECT rect = {offset_x, offset_y, offset_x + width, offset_y + height};

    // Draw centered text
    DrawText(hdc, itemName.c_str(), itemName.length(), &rect,
             DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    // Clean up resources
    SelectObject(hdc, hOldBrush);
    DeleteObject(hBrush);
}