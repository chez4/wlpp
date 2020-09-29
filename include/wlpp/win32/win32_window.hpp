/*
 * wlpp Copyright 2020 Max Burns
 * See LICENSE for more information.
 */

#ifndef WLPP_WIN32_WINDOW_HPP
#define WLPP_WIN32_WINDOW_HPP

#include <string>

#include <windef.h>
#include <winuser.h>

#include <wlpp/window.hpp>

namespace wlpp {

class win32_window : public window {
private:
    HWND wind;
    WNDCLASS wind_class;

    HINSTANCE inst;

    bool quit;
    mutable bool shown;

    static LRESULT CALLBACK window_callback(HWND, UINT, WPARAM, LPARAM);
    LRESULT CALLBACK window_proc(HWND, UINT, WPARAM, LPARAM);

public:
    explicit win32_window(const std::string &, int = CW_USEDEFAULT, int = CW_USEDEFAULT, int = CW_USEDEFAULT, int = CW_USEDEFAULT);

    ~win32_window();

    win32_window(const win32_window &) = delete;

    win32_window(win32_window &&) noexcept;

    win32_window &operator=(win32_window);

    friend void swap(win32_window &, win32_window &);

    void poll_events() const override;

    void wait_events() const override;

    void show() const override;

    void hide() const override;

    bool has_closed() const override;
};

}

#endif //WLPP_WIN32_WINDOW_HPP
