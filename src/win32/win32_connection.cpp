// Copyright (C) 2020-2021 Max Burns
// See LICENSE for more information
// wlpp   - src/win32/win32_connection.cpp
// Author - chez4 29/09/2020

#include <wlpp/win32/win32_connection.hpp>

#include <windef.h>
#include <winuser.h>

#include <wlpp/win32/win32_window.hpp>

namespace wlpp {

LRESULT CALLBACK win32_connection::window_callback(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
    win32_window *wind = (win32_window *) GetWindowLongPtr(hwnd, GWLP_USERDATA);
    if (wind == nullptr) return DefWindowProc(hwnd, msg, w_param, l_param);
    else return wind->callback(hwnd, msg, w_param, l_param);
}

win32_connection::win32_connection()
    : inst(GetModuleHandle(nullptr))
    , default_wc()
{
    default_wc.lpfnWndProc = window_callback;
    default_wc.hInstance = inst;
    default_wc.lpszClassName = "wlpp Default Class";
    RegisterClass(&default_wc);
}

void win32_connection::send() const
{
}

}
