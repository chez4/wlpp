// Copyright (C) 2020-2021 Max Burns
// See LICENSE for more information
// wlpp   - include/wlpp/xcb/xcb_connection.hpp
// Author - chez4 20/09/2020

#ifndef WLPP_XCB_CONNECTION_HPP
#define WLPP_XCB_CONNECTION_HPP

#include <string>

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
    xcb_connection_t *conn;

    static std::string get_connection_error_string(int);

    xcb_connection(const char *, int *);

public:
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
     * Connects to X server through XCB, using the &c DISPLAY environment
     * variable for the display.
     *
     * @param [in] screen Preferred screen number.
     *
     * @overload
     */
    explicit xcb_connection(int screen = 0);

    ~xcb_connection();

    xcb_connection(const xcb_connection &) = delete;

    /**
     * Constructs connection from move.
     *
     * @param[in, out] other Connection to move from.
     */
    xcb_connection(xcb_connection &&other) noexcept;

    /**
     * Assigns connection to other connection.
     *
     * @param[in, out] other Connection to assign to.
     *
     * @returns Reference to this newly assigned connection.
     */
    xcb_connection &operator=(xcb_connection other);

    /**
     * Swaps two xcb_connections.
     *
     * @param[in, out] a Swap operand.
     * @param[in, out] b Swap operand.
     *
     * @relatesalso xcb_connection
     */
    friend void swap(xcb_connection &a, xcb_connection &b);

    void send() const;
};

}

#endif // WLPP_XCB_CONNECTION_HPP
