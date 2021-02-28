// Copyright (C) 2020-2021 Max Burns
// See LICENSE for more information
// wlpp   - src/win32/win32_window.cpp
// Author - chez4 22/09/2020

#include <wlpp/win32/win32_window.hpp>

#include <memory>
#include <string>
#include <utility>

#include <windef.h>
#include <winuser.h>

#include <wlpp/win32/win32_connection.hpp>
#include <wlpp/window_error.hpp>

namespace wlpp {

::LRESULT CALLBACK win32_window::callback(::UINT msg, ::WPARAM w_param, ::LPARAM l_param)
{
    switch (msg) {
        case WM_DESTROY:
            ::PostQuitMessage(0);
            quit = true;
            return 0;
    }
    return ::DefWindowProc(wind, msg, w_param, l_param);
}

win32_window::win32_window(std::shared_ptr<win32_connection> conn, int width, int height, int x, int y, const std::string &title)
    : conn(std::move(conn))
    , wind(CreateWindowEx(0, this->conn->default_wc.lpszClassName, title.c_str(), WS_OVERLAPPEDWINDOW, x, y, width, height, nullptr, nullptr, this->conn->inst, nullptr))
    , shown(false)
    , quit(false)
{
    if (wind == nullptr)
        throw window_error(win32_connection::get_last_error_string());

    ::SetWindowLongPtr(wind, GWLP_USERDATA, (::LONG_PTR) this);
}

win32_window::win32_window(std::shared_ptr<win32_connection> conn, int width, int height, const std::string &title)
    : win32_window(std::move(conn), width, height, CW_USEDEFAULT, CW_USEDEFAULT, title)
{
}

win32_window::win32_window(std::shared_ptr<win32_connection> conn, const std::string &title)
    : win32_window(std::move(conn), CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, title)
{
}

win32_window::win32_window(win32_window &&other) noexcept
    : conn(std::move(other.conn))
    , wind(other.wind)
    , shown(other.shown)
    , quit(other.quit)
{
    other.conn = nullptr;
    other.wind = nullptr;
}

win32_window::~win32_window()
{
    if (wind != nullptr) ::DestroyWindow(wind);
}

win32_window &win32_window::operator=(win32_window other)
{
    if (this != &other) { swap(*this, other); }
    return *this;
}

void swap(win32_window &a, win32_window &b)
{
    std::swap(a.conn, b.conn);
    std::swap(a.wind, b.wind);
    std::swap(a.shown, b.shown);
    std::swap(a.quit, b.quit);
}

void win32_window::show() const
{
    ::ShowWindow(wind, shown ? SW_SHOW : SW_SHOWNORMAL);
    shown = true;
}

void win32_window::hide() const
{
    ::ShowWindow(wind, SW_HIDE);
}

bool win32_window::has_quit() const
{
    return quit;
}

}
