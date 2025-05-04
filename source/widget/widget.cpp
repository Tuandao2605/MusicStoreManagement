#include "widget.h"

void Widget::display(HDC hdc) const
{
    Rectangle(hdc, offset_x, offset_y, offset_x + width, offset_y + height);
}