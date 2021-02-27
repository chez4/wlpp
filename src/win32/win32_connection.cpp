// Copyright (C) 2020-2021 Max Burns
// See LICENSE for more information
// wlpp   - src/win32/win32_connection.cpp
// Author - chez4 29/09/2020

#include <wlpp/win32/win32_connection.hpp>

#include <errhandlingapi.h>
#include <winbase.h>
#include <wincon.h>
#include <windef.h>
#include <winuser.h>

#include <wlpp/connection_error.hpp>
#include <wlpp/win32/win32_window.hpp>

namespace wlpp {

std::string win32_connection::get_last_error_string()
{
    ::LPTSTR msg_buf;
    ::DWORD error = ::GetLastError();
    ::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                  nullptr, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (::LPTSTR) &msg_buf, 0, nullptr);
    std::string err = msg_buf;
    ::LocalFree(msg_buf);
    return err;
}

::LRESULT CALLBACK win32_connection::window_callback(::HWND hwnd, ::UINT msg, ::WPARAM w_param, ::LPARAM l_param)
{
    win32_window *wind = (win32_window *) ::GetWindowLongPtr(hwnd, GWLP_USERDATA);
    if (wind == nullptr) return ::DefWindowProc(hwnd, msg, w_param, l_param);
    else return wind->callback(msg, w_param, l_param);
}

win32_connection::win32_connection()
    : inst(::GetModuleHandle(nullptr))
    , default_wc()
    , closed(false)
{
    default_wc.lpfnWndProc = window_callback;
    default_wc.hInstance = inst;
    default_wc.lpszClassName = "wlpp Default Class";
    ::RegisterClass(&default_wc);

    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

void win32_connection::send() const
{
}

void win32_connection::wait_events() const
{
    MSG msg;
    switch (::GetMessage(&msg, nullptr, 0, 0)) {
        case -1:
            throw connection_error(get_last_error_string());

        case 0:
            closed = true;
            break;

        default:
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
    }
}

void win32_connection::poll_events() const
{
    ::MSG msg;
    if (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
        if (msg.message == WM_QUIT) {
            closed = true;
        } else {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }
    }
}

bool win32_connection::has_closed() const
{
    return closed;
}

}
