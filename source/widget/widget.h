#pragma once

#include <iostream>
#include <windows.h>

using namespace std;

class Widget {
protected:
    int offset_x;
    int offset_y;
    int width;
    int height;

public:
    Widget() : width(0), height(0), offset_x(0), offset_y(0) {}
    Widget(int w, int h) : width(w), height(h), offset_x(0), offset_y(0) {}

    int getWidth() const { return width; }
    int getHeight() const { return height; }

    void setWidth(int w) { width = w; }
    void setHeight(int h) { height = h; }

    void setOffsetX(int x) { offset_x = x; }
    void setOffsetY(int y) { offset_y = y; }

    int getOffsetX() const { return offset_x; }
    int getOffsetY() const { return offset_y; }
    
    virtual void display(HDC hdc) const;

    virtual ~Widget() {}
};