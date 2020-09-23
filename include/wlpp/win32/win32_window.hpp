/*
 * wlpp Copyright 2020 Max Burns
 * See LICENSE for more information.
 */

#ifndef WLPP_WIN32_WINDOW_HPP
#define WLPP_WIN32_WINDOW_HPP

#include <wlpp/window.hpp>

#include <windows.h>

namespace wlpp {

class win32_window : public window {
private:
    HWND wind;

public:
    win32_window();

    ~win32_window();

    win32_window(win32_window &&) noexcept;

    win32_window &operator=(win32_window);

    friend void swap(win32_window &, win32_window &);

    void show() const override;

    void hide() const override;
};

}

#endif //WLPP_WIN32_WINDOW_HPP
