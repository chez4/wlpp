// Copyright (C) 2020-2021 Max Burns
// See LICENSE for more information
// wlpp   - src/win32/win32_connection.cpp
// Author - chez4 29/09/2020

#include <wlpp/win32/win32_connection.hpp>

#include <winuser.h>

namespace wlpp {

// temporary
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

HINSTANCE &win32_connection::get_instance()
{
    return inst;
}

WNDCLASS &win32_connection::get_default_class()
{
    return default_wc;
}

win32_connection::win32_connection()
    : inst(GetModuleHandle(nullptr))
    , default_wc()
{
    default_wc.lpfnWndProc = WindowProc;
    default_wc.hInstance = inst;
    default_wc.lpszClassName = "wlpp Default Class";
    RegisterClass(&default_wc);
}

void win32_connection::send() const
{
}

}
