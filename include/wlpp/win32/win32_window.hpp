// Copyright (C) 2020-2021 Max Burns
// See LICENSE for more information
// wlpp   - include/wlpp/win32/win32_window.hpp
// Author - chez4 22/09/2020

#ifndef WLPP_WIN32_WINDOW_HPP
#define WLPP_WIN32_WINDOW_HPP

#include <memory>
#include <string>

#include <windef.h>

#include <wlpp/win32/win32_connection.hpp>
#include <wlpp/window.hpp>

namespace wlpp {

/**
 * Window object using win32 API.
 *
 * Acts as a dynamic window object bound through a @c connection.
 *
 * @warning This class and header should only be used on a platform using win32.
 *
 * @see window
 * @see connection
 */
class win32_window : public window<win32_window> {
private:
    std::shared_ptr<win32_connection> conn;

    HWND wind;

    mutable bool shown;

    friend LRESULT CALLBACK win32_connection::window_callback(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);

    LRESULT CALLBACK callback(HWND, UINT, WPARAM, LPARAM);

public:
    /**
     * Instantiates window object with size and position.
     *
     * Constructs a win32 window at specified position using @p x and @p y , and
     * with size @p width pixels x @p height pixels. A title will be associated
     * with the window if specified by @title , otherwise it will be blank. This
     * window will be tied to the shared @p conn passed to it.
     *
     * @param [in] conn Shared connection pointer to associate with.
     * @param [in] width Width in pixels of window.
     * @param [in] height Height in pixels of window.
     * @param [in] x X coordinate of top-left corner of window.
     * @param [in] y Y coordinate of top-left corner of window.
     * @param [in] title Title to associate with window.
     *
     * @throws wlpp::window_error Thrown if the window failed to create.
     */
    win32_window(std::shared_ptr<win32_connection> conn, int width, int height, int x, int y, const std::string &title = "");

    /**
     * Instantiates window object with size.
     *
     * @overload
     */
    win32_window(std::shared_ptr<win32_connection> conn, int width, int height, const std::string &title = "");

    /**
     * Instantiates window object.
     *
     * @overload
     */
    explicit win32_window(std::shared_ptr<win32_connection> conn, const std::string &title = "");

    ~win32_window();

    win32_window(const win32_window &) = delete;

    win32_window(win32_window &&other) noexcept;

    win32_window &operator=(win32_window other);

    /**
     * Swaps two @c win32_window s.
     *
     * @param[in, out] a Swap operand.
     * @param[in, out] b Swap operand.
     *
     * @relatesalso win32_window
     */
    friend void swap(win32_window &a, win32_window &b);

    /**
     * Makes window visible on screen.
     */
    void show() const;

    /**
     * Makes window invisible on screen.
     */
    void hide() const;
};

}

#endif //WLPP_WIN32_WINDOW_HPP
