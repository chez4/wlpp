/*
 * wlpp Copyright 2020 Max Burns
 * See LICENSE for more information.
 */

#include <wlpp/win32/win32_window.hpp>

#include <utility>

namespace wlpp {

win32_window::win32_window()
{
    WNDCLASS wc = {};
    wc.lpfnWndProc

    wind = CreateWindowEx(
            0,
            CLASS_NAME,                     // Window class
            L"Learn to Program Windows",    // Window text
            WS_OVERLAPPEDWINDOW,            // Window style

            // Size and position
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

            nullptr,       // Parent window
            nullptr,       // Menu
            nullptr,  // Instance handle
            nullptr        // Additional application data
    );

}

win32_window::~win32_window()
{

}

win32_window::win32_window(win32_window &&other) noexcept
    : wind(other.wind)
{
}

win32_window &win32_window::operator=(win32_window other)
{
    if (this != &other) swap(*this, other);
    return *this;
}

void swap(win32_window &a, win32_window &b)
{
    std::swap(a.wind, b.wind);
}

}
