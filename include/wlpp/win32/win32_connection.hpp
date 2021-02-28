// Copyright (C) 2020-2021 Max Burns
// See LICENSE for more information
// wlpp   - include/wlpp/win32/win32_connection.hpp
// Author - chez4 29/09/2020

#ifndef WLPP_WIN32_CONNECTION_HPP
#define WLPP_WIN32_CONNECTION_HPP

#include <windef.h>
#include <winuser.h>

#include <string>

#include <wlpp/connection.hpp>

namespace wlpp {

/**
 * Connection to win32 API.
 *
 * Provides an interface to the win32 API for management of windows and event
 * handling.
 *
 * @warning This class and header should only be used on a platform using win32.
 *
 * @see connection
 */
class win32_connection : public connection<win32_connection> {
private:
    static std::string get_last_error_string();

    static ::LRESULT CALLBACK window_callback(::HWND, ::UINT, ::WPARAM, ::LPARAM);

    ::HINSTANCE inst;

    ::WNDCLASS default_wc;

    mutable bool closed;

public:
    friend class win32_window;

    /**
     * Connects to win32 API.
     *
     * Currently only obtains a @c HINSTANCE through @c GetModuleHandle() .
     */
    win32_connection();

    /**
     * Flushes all pending messages to connection.
     *
     * Currently serves no purpose on win32 platforms, and can be safely
     * ignored.
     */
    void send() const;

    /**
     * Handles the next event on the calling thread's event queue, blocking the
     * thread if a message is not yet present.
     *
     * This function will block the current thread if no messages are present,
     * returning when the next posted event has been handled.
     *
     * @throws wlpp::connection_error Thrown if there was an error handling
     * the event.
     */
    void wait_events() const;

    /**
     * Handles the next event on the calling thread's event queue, returning if
     * no messages are present.
     *
     * This function will not block the current thread if no messages are
     * present, returning immediately.
     */
    void poll_events() const;

    /**
     * Returns whether the connection to the API has been closed.
     *
     * @return True if connection has been closed.
     */
    bool has_closed() const;
};

}

#endif // WLPP_WIN32_CONNECTION_HPP
