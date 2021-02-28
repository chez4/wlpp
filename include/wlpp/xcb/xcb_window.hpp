// Copyright (C) 2020-2021 Max Burns
// See LICENSE for more information
// wlpp   - include/wlpp/xcb/xcb_window.hpp
// Author - chez4 20/09/2020

#ifndef WLPP_XCB_WINDOW_HPP
#define WLPP_XCB_WINDOW_HPP

#include <memory>

#include <xcb/xcb.h>

#include <wlpp/window.hpp>
#include <wlpp/xcb/xcb_connection.hpp>

namespace wlpp {

/**
 * Window object using XCB API.
 *
 * Acts as a dynamic window object bound through a @c connection.
 *
 * @warning This class and header should only be used on a platform using X11.
 *
 * @see window
 * @see connection
 */
class xcb_window : window<xcb_window> {
private:
    std::shared_ptr<xcb_connection> conn;

    ::xcb_window_t wind;

    ::xcb_screen_t screen;

public:
    /**
     * Instantiates window object with size and position.
     *
     * Constructs a XCB window at specified position using @p x and @p y , and
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
     * @throws wlpp::connection_error Thrown if the requested screen was not
     * found.
     */
    xcb_window(std::shared_ptr<xcb_connection> conn, int width, int height, int x, int y, const std::string &title = "");

    /**
     * Instantiates window object with size.
     *
     * @param [in] conn Shared connection pointer to associate with.
     * @param [in] width Width in pixels of window.
     * @param [in] height Height in pixels of window.
     * @param [in] title Title to associate with window.
     *
     * @overload
     */
    xcb_window(std::shared_ptr<xcb_connection> conn, int width, int height, const std::string &title = "");

    /**
     * Instantiates window object.
     *
     * @param [in] conn Shared connection pointer to associate with.
     * @param [in] title Title to associate with window.
     *
     * @overload
     */
    explicit xcb_window(std::shared_ptr<xcb_connection> conn, const std::string &title = "");

    ~xcb_window();

    xcb_window(const xcb_window &) = delete;

    xcb_window(xcb_window &&other) noexcept;

    xcb_window &operator=(xcb_window other);

    /**
     * Swaps two @c xcb_window s.
     *
     * @param[in, out] a Swap operand.
     * @param[in, out] b Swap operand.
     *
     * @relatesalso xcb_window
     */
    friend void swap(xcb_window &a, xcb_window &b);

    /**
     * Sets the title of the window to @p title .
     *
     * @param[in] title Title to associate with window.
     */
    void set_title(const std::string &title) const;

    /**
     * Makes window visible on screen.
     */
    void show() const;

    /**
     * Makes window invisible on screen.
     */
    void hide() const;

    /**
     * Returns whether the window has been destroyed.
     *
     * @return True if window has been destroyed.
     */
    bool has_quit() const;
};

}

#endif // WLPP_XCB_WINDOW_HPP
