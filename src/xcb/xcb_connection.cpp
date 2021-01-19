// Copyright (C) 2020-2021 Max Burns
// See LICENSE for more information
// wlpp   - src/xcb/xcb_connection.cpp
// Author - chez4 20/09/2020

#include <wlpp/xcb/xcb_connection.hpp>

#include <utility>

#include <xcb/xcb.h>

#include <wlpp/connection_error.hpp>

namespace wlpp {

xcb_connection::xcb_connection()
    : conn(xcb_connect(nullptr, nullptr))
{
    switch (xcb_connection_has_error(conn)) {
        case 0:
            break;

        case XCB_CONN_ERROR:
            throw connection_error("XCB: Socket/pipe/stream error");

        case XCB_CONN_CLOSED_EXT_NOTSUPPORTED:
            throw connection_error("XCB: Extension unsupported");

        case XCB_CONN_CLOSED_MEM_INSUFFICIENT:
            throw connection_error("XCB: Insufficient memory");

        case XCB_CONN_CLOSED_REQ_LEN_EXCEED:
            throw connection_error("XCB: Accepted server request length exceeded");

        case XCB_CONN_CLOSED_PARSE_ERR:
            throw connection_error("XCB: Error parsing display string");

        case XCB_CONN_CLOSED_INVALID_SCREEN:
            throw connection_error("XCB: No screen matching display on server");

        default:
            throw connection_error("XCB: Unknown");
    }
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
