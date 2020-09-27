/*
 * wlpp Copyright 2020 Max Burns
 * See LICENSE for more information.
 */

#include <wlpp/win32/win32_window.hpp>

#include <string>
#include <utility>

#include <windef.h>
#include <winuser.h>

namespace wlpp {

LRESULT win32_window::window_callback(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
    win32_window *wind = (win32_window *) GetWindowLongPtr(hwnd, GWLP_USERDATA);
    if (wind == nullptr) return DefWindowProc(hwnd, msg, w_param, l_param);
    else return wind->window_proc(hwnd, msg, w_param, l_param);
}

LRESULT win32_window::window_proc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
    switch (msg) {
        case WM_DESTROY:
            quit = true;
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, msg, w_param, l_param);
}

win32_window::win32_window(const std::string &name, int x, int y, int width, int height)
    : wind_class()
    , quit(false)
    , shown(false)
{
    inst = GetModuleHandle(nullptr);

    wind_class.lpfnWndProc = window_callback;
    wind_class.hInstance = inst;
    wind_class.lpszClassName = (name + " wlpp Class Name").c_str();
    RegisterClass(&wind_class);

    wind = CreateWindowEx(0, wind_class.lpszClassName, name.c_str(), WS_OVERLAPPEDWINDOW, x, y, width, height, nullptr, nullptr, inst, nullptr);
    SetWindowLongPtr(wind, GWLP_USERDATA, (LONG_PTR) this);
}

win32_window::~win32_window()
{
    if (wind != nullptr) DestroyWindow(wind);
}

win32_window::win32_window(win32_window &&other) noexcept
    : wind(other.wind)
    , wind_class(other.wind_class)
    , inst(other.inst)
    , quit(other.quit)
    , shown(other.shown)
{
    SetWindowLongPtr(wind, GWLP_USERDATA, (LONG_PTR) this);

    other.wind = nullptr;
    other.inst = nullptr;
}

win32_window &win32_window::operator=(win32_window other)
{
    if (this != &other) swap(*this, other);
    return *this;
}

void swap(win32_window &a, win32_window &b)
{
    SetWindowLongPtr(a.wind, GWLP_USERDATA, (LONG_PTR) &b);
    SetWindowLongPtr(b.wind, GWLP_USERDATA, (LONG_PTR) &a);

    std::swap(a.wind, b.wind);
    std::swap(a.wind_class, b.wind_class);
    std::swap(a.inst, b.inst);
    std::swap(a.quit, b.quit);
    std::swap(a.shown, b.shown);
}

void win32_window::poll_events() const
{
    MSG msg = {};
    PeekMessage(&msg, wind, 0, 0, PM_REMOVE);
    TranslateMessage(&msg);
    DispatchMessage(&msg);
}

void win32_window::wait_events() const
{
    MSG msg = {};
    GetMessage(&msg, wind, 0, 0);
    TranslateMessage(&msg);
    DispatchMessage(&msg);
}

void win32_window::show() const
{
    ShowWindow(wind, shown ? SW_SHOW : SW_SHOWNORMAL);
    shown = true;
}

void win32_window::hide() const
{
    ShowWindow(wind, SW_HIDE);
}

bool win32_window::has_closed() const
{
    return quit;
}

}
