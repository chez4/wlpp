// Copyright (C) 2020-2021 Max Burns
// See LICENSE for more information
// wlpp   - src/xcb/xcb_connection.cpp
// Author - chez4 20/09/2020

#include <wlpp/xcb/xcb_connection.hpp>

#include <stdexcept>
#include <string>
#include <utility>

#include <cstdint>

#include <xcb/xcb.h>

#include <wlpp/connection_error.hpp>

namespace wlpp {

std::string xcb_connection::get_connection_error_string(int error)
{
    switch (error) {
        case 0:
            return "Success";

        case XCB_CONN_ERROR:
            return "Socket/pipe/stream error";

        case XCB_CONN_CLOSED_EXT_NOTSUPPORTED:
            return "Extension not supported";

        case XCB_CONN_CLOSED_MEM_INSUFFICIENT:
            return "Insufficient memory";

        case XCB_CONN_CLOSED_REQ_LEN_EXCEED:
            return "Accepted server request length exceeded";

        case XCB_CONN_CLOSED_PARSE_ERR:
            return "Error parsing display string";

        case XCB_CONN_CLOSED_INVALID_SCREEN:
            return "No screen matching display on server";

        default:
            return "Unknown";
    }
}

xcb_connection::xcb_connection(const char *display, const int *screen)
    : screen_pref(*screen)
    , conn(::xcb_connect(display, &screen_pref))
{
    int error = ::xcb_connection_has_error(conn);
    if (error != 0) {
        if (error == XCB_CONN_CLOSED_PARSE_ERR)
            throw std::invalid_argument(get_connection_error_string(error));
        else
            throw connection_error(get_connection_error_string(error));
    }

    setup = ::xcb_get_setup(conn);
}

xcb_connection_t *xcb_connection::get() const
{
    return conn;
}

std::uint32_t xcb_connection::generate_id() const
{
    return ::xcb_generate_id(conn);
}

::xcb_screen_t xcb_connection::get_screen(int num) const
{
    ::xcb_screen_iterator_t iter = ::xcb_setup_roots_iterator(setup);
    int screens = iter.rem;
    while (iter.rem >= 0) {
        if (num == screens - iter.rem)
            return *iter.data;
        ::xcb_screen_next(&iter);
    }

    throw connection_error("Requested screen \"" + std::to_string(num) + "\" was not found on X connection");
}

::xcb_screen_t xcb_connection::get_preffered_screen() const
{
    return get_screen(screen_pref);
}

xcb_connection::xcb_connection(const std::string &display, int screen)
    : xcb_connection(display.c_str(), &screen)
{
}


xcb_connection::xcb_connection(int screen)
    : xcb_connection(nullptr, &screen)
{
}

xcb_connection::~xcb_connection()
{
    if (conn != nullptr) ::xcb_disconnect(conn);
}

xcb_connection::xcb_connection(xcb_connection &&other) noexcept
    : screen_pref(other.screen_pref)
    , conn(other.conn)
    , setup(other.setup)
{
    other.conn = nullptr;
    other.setup = nullptr;
}

xcb_connection &xcb_connection::operator=(xcb_connection other)
{
    if (this != &other) swap(*this, other);
    return *this;
}

void swap(xcb_connection &a, xcb_connection &b)
{
    std::swap(a.screen_pref, b.screen_pref);
    std::swap(a.conn, b.conn);
    std::swap(a.setup, b.setup);
}

void xcb_connection::send() const
{
    ::xcb_flush(conn);
}

void xcb_connection::wait_events() const
{

}

void xcb_connection::poll_events() const
{

}

bool xcb_connection::has_closed() const
{
    return false;
}

}
