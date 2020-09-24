/*
 * wlpp Copyright 2020 Max Burns
 * See LICENSE for more information.
 */

#include <wlpp/xcb/xcb_connection.hpp>

#include <string>
#include <utility>

#include <cstdint>

#include <xcb/xcb.h>

#include <window_api_error.hpp>
#include <wlpp/xcb/xcb_screen.hpp>
#include <wlpp/xcb/xcb_window.hpp>

namespace wlpp {

xcb_connection::xcb_connection()
    : screen_pref()
{
    conn = xcb_connect(nullptr, &screen_pref);
    setup = xcb_get_setup(conn);
}

xcb_connection::~xcb_connection()
{
    if (conn != nullptr) {
        xcb_disconnect(conn);
    }
}

xcb_connection::xcb_connection(xcb_connection &&other) noexcept
    : conn(other.conn)
    , screen_pref(other.screen_pref)
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
    std::swap(a.conn, b.conn);
    std::swap(a.screen_pref, b.screen_pref);
    std::swap(a.setup, b.setup);
}

xcb_connection_t *xcb_connection::get() const
{
    return conn;
}

void xcb_connection::flush() const
{
    xcb_flush(conn);
}

std::uint32_t xcb_connection::generate_id() const
{
    return xcb_generate_id(conn);
}

xcb_screen xcb_connection::get_screen(int num) const
{
    xcb_screen_iterator_t iter = xcb_setup_roots_iterator(setup);
    while (iter.rem >= 0) {
        if (num == iter.rem)
            return xcb_screen(*iter.data);
        xcb_screen_next(&iter);
    }

    throw window_api_error("Requested screen \"" + std::to_string(num) + "\" was not found on X connection");
}

xcb_screen xcb_connection::get_default_screen() const
{
    return get_screen(screen_pref);
}

void xcb_connection::map_window(const xcb_window &wind) const
{
    xcb_map_window(conn, wind.get());
}

void xcb_connection::unmap_window(const xcb_window &wind) const
{
    xcb_unmap_window(conn, wind.get());
}

}
