// Copyright (C) 2020-2021 Max Burns
// See LICENSE for more information
// wlpp   - include/wlpp/xcb/xcb_connection.hpp
// Author - chez4 20/09/2020

#ifndef WLPP_XCB_CONNECTION_HPP
#define WLPP_XCB_CONNECTION_HPP

#include <string>

#include <cstdint>

#include <xcb/xcb.h>

#include <wlpp/connection.hpp>

namespace wlpp {

/**
 * Connection to X11 display server through XCB.
 *
 * Provides an interface to the X11 display server, along with management of
 * windows and event handling.
 *
 * @warning This class and header should only be used on a platform using X11.
 *
 * @see connection
 */
class xcb_connection : public connection<xcb_connection> {
private:
    static std::string get_connection_error_string(int);

    int screen_pref;

    ::xcb_connection_t *conn;

    const ::xcb_setup_t *setup;

    xcb_connection(const char *, const int *);

    xcb_connection_t *get() const;

    std::uint32_t generate_id() const;

    ::xcb_screen_t get_screen(int) const;

    ::xcb_screen_t get_preffered_screen() const;

public:
    friend class xcb_window;

    /**
     * Connects to X server specified by @p display through XCB.
     *
     * A connection is made to the X server using XCB, and a &c xcb_connection
     * is constructed. A screen number can be specified if one is preferred,
     * otherwise the screen number will default to 0.
     *
     * @param [in] display Name of display.
     * @param [in] screen Preferred screen number.
     *
     * @throws std::invalid_argument Thrown if @p display could not be parsed.
     * @throws wlpp::connection_error Thrown if an error occured during
     * connection to the X server.
     */
    explicit xcb_connection(const std::string &display, int screen = 0);

    /**
     * Connects to X server through XCB, using the @c DISPLAY environment
     * variable for the display.
     *
     * @param [in] screen Preferred screen number.
     *
     * @overload
     */
    explicit xcb_connection(int screen = 0);

    ~xcb_connection();

    xcb_connection(const xcb_connection &) = delete;

    xcb_connection(xcb_connection &&other) noexcept;

    xcb_connection &operator=(xcb_connection other);

    /**
     * Swaps two @c xcb_connection s.
     *
     * @param[in, out] a Swap operand.
     * @param[in, out] b Swap operand.
     *
     * @relatesalso xcb_connection
     */
    friend void swap(xcb_connection &a, xcb_connection &b);

    /**
     * Flushes all pending messages to connection.
     *
     * Should be called after most operations.
     */
    void send() const;

    void wait_events() const;

    void poll_events() const;

    bool has_closed() const;
};

}

#endif // WLPP_XCB_CONNECTION_HPP
