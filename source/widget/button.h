#pragma once

#include "widget.h"

class Button : public Widget
{
private:
    string itemName;
public:
    bool isSelected = false;
    void setSelected(bool selected) { isSelected = selected; }
    bool getSelected() const { return isSelected; }

    Button(int w, int h, const string& name) : Widget(w, h), itemName(name) {}
    void display(HDC hdc) const override;
    ~Button() {}
};