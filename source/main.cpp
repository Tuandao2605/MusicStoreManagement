// Music Store Manangement System in C++ Design and Developed by CodeWithC.com

#include <iostream>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <conio.h>
#include <ctime>
#include "mysql.h"

#include "music_repository.h"

#include "widget/export.h"

using namespace std;

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 900;
const char *WINDOW_TITLE = "Music Store Management System";
const char WINDOW_CLASS_NAME[] = "MusicStoreWindowClass";

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HomeScreen* homeWidget = nullptr;

    switch (uMsg)
    {
    case WM_CREATE:
        homeWidget = new HomeScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        if (homeWidget) {
            homeWidget->display(hdc);
        }
        EndPaint(hwnd, &ps);
        return 0;
    }

    case WM_KEYDOWN:
        if (homeWidget) {
            switch (wParam)
            {
            case VK_UP:
                homeWidget->previousItem();
                InvalidateRect(hwnd, NULL, TRUE);
                break;
            case VK_DOWN:
                homeWidget->nextItem();
                InvalidateRect(hwnd, NULL, TRUE);
                break;
            }
        }
        return 0;

    case WM_DESTROY:
        delete homeWidget;
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = WINDOW_CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,                   // Extended style
        WINDOW_CLASS_NAME,   // Class name
        WINDOW_TITLE,        // Title
        WS_OVERLAPPEDWINDOW, // Style

        CW_USEDEFAULT, CW_USEDEFAULT, SCREEN_WIDTH, SCREEN_HEIGHT,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL)
        return 0;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Message loop
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}