// Copyright (C) 2020-2021 Max Burns
// See LICENSE for more information
// wlpp   - include/wlpp/xcb/xcb_connection.hpp
// Author - chez4 20/09/2020

#ifndef WLPP_XCB_CONNECTION_HPP
#define WLPP_XCB_CONNECTION_HPP

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

public:
    /**
     * Constructs connection.
     *
     * @exceptsafe Will not throw exceptions.
     */
    xcb_connection();

    /**
     * Destructs connection.
     *
     * @exceptsafe Will not throw exceptions.
     */
    ~xcb_connection();

    xcb_connection(const xcb_connection &) = delete;

    /**
     * Constructs connection from move.
     *
     * @param[in, out] other Connection to move from.
     *
     * @exceptsafe Will not throw exceptions.
     */
    xcb_connection(xcb_connection &&other) noexcept;

    /**
     * Assigns connection to other connection.
     *
     * @param[in, out] other Connection to assign to.
     *
     * @returns Reference to this newly assigned connection.
     *
     * @exceptsafe Will not throw exceptions.
     */
    xcb_connection &operator=(xcb_connection other);

    /**
     * Swaps two xcb_connections.
     *
     * @param[in, out] a Swap operand.
     * @param[in, out] b Swap operand.
     *
     * @exceptsafe Will not throw exceptions.
     *
     * @relatesalso xcb_connection
     */
    friend void swap(xcb_connection &a, xcb_connection &b);

    void send() const;
};

}

#endif // WLPP_XCB_CONNECTION_HPP
