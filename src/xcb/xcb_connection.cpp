// Copyright (C) 2020-2021 Max Burns
// See LICENSE for more information
// wlpp   - src/xcb/xcb_connection.cpp
// Author - chez4 20/09/2020

#include <wlpp/xcb/xcb_connection.hpp>

#include <stdexcept>
#include <string>
#include <utility>

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

xcb_connection::xcb_connection(const char *display, int *screen)
    : conn(xcb_connect(display, screen))
{
    int error = xcb_connection_has_error(conn);
    if (error != 0) {
        xcb_disconnect(conn);
        conn = nullptr;

        if (error == XCB_CONN_CLOSED_PARSE_ERR)
            throw std::invalid_argument(get_connection_error_string(error));
        else
            throw connection_error(get_connection_error_string(error));
    }
}

xcb_connection::xcb_connection(const std::string &display, int screen)
    : xcb_connection(display.c_str(), &screen)
{
}

xcb_connection::xcb_connection(int screen) : xcb_connection(nullptr, &screen)
{
}

xcb_connection::~xcb_connection()
{
    xcb_disconnect(conn);
}

xcb_connection::xcb_connection(xcb_connection &&other) noexcept
    : conn(other.conn)
{
    other.conn = nullptr;
}

xcb_connection &xcb_connection::operator=(xcb_connection other)
{
    if (this != &other) swap(*this, other);
    return *this;
}

void swap(xcb_connection &a, xcb_connection &b)
{
    std::swap(a.conn, b.conn);
}

void xcb_connection::send() const
{
    xcb_flush(conn);
}

}
