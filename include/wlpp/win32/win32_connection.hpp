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

    HINSTANCE inst;

    WNDCLASS default_wc;

    static LRESULT CALLBACK window_callback(HWND, UINT, WPARAM, LPARAM);

public:
    friend class win32_window;

    /**
     * Connects to win32 API.
     *
     * Currently only obtains a @c HINSTANCE through @c GetModuleHandle() .
     */
    win32_connection();

    /**
     * Swaps two @c win32_window s.
     *
     * @param[in, out] a Swap operand.
     * @param[in, out] b Swap operand.
     *
     * @relatesalso win32_window
     */
    void send() const;
};

}

#endif // WLPP_WIN32_CONNECTION_HPP
