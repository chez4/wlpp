/*
 * wlpp Copyright 2020 Max Burns
 * See LICENSE for more information.
 */

#include <wlpp/win32/win32_window.hpp>

#include <utility>

namespace wlpp {

static LRESULT CALLBACK window_proc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
    switch (msg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, msg, w_param, l_param);
}

win32_window::win32_window()
{
    const char CLASS_NAME[] = "Sample Window Class";

    WNDCLASS wc = {};
    wc.lpfnWndProc = window_proc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    wind = CreateWindowEx(0, CLASS_NAME, "Learn to Program Windows", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, GetModuleHandle(nullptr), nullptr);
    ShowWindow(wind, 1);

    MSG msg = { };
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
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

void win32_window::show() const
{

}

void win32_window::hide() const
{

}

}
