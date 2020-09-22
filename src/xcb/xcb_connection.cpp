/*
 * wlpp Copyright 2020 Max Burns
 * See LICENSE for more information.
 */

#include <wlpp/xcb/xcb_connection.hpp>

#include <string>
#include <utility>

#include <cstdint>

#include <xcb/xcb.h>

#include <wlpp/window_api_error.hpp>
#include <wlpp/xcb/xcb_screen.hpp>

namespace wlpp {

xcb_connection::xcb_connection()
    : screen_pref()
{
    p_connection = xcb_connect(nullptr, &screen_pref);

    p_setup = xcb_get_setup(p_connection);
}

xcb_connection::~xcb_connection()
{
    if (p_connection != nullptr) {
        xcb_disconnect(p_connection);
    }
}

xcb_connection::xcb_connection(xcb_connection &&other) noexcept
    : p_connection(other.p_connection)
    , screen_pref(other.screen_pref)
    , p_setup(other.p_setup)
{
    other.p_connection = nullptr;
    other.p_setup = nullptr;
}

xcb_connection &xcb_connection::operator=(xcb_connection other)
{
    if (this != &other) swap(*this, other);
    return *this;
}

void swap(xcb_connection &a, xcb_connection &b)
{
    std::swap(a.p_connection, b.p_connection);
    std::swap(a.screen_pref, b.screen_pref);
    std::swap(a.p_setup, b.p_setup);
}

xcb_connection_t *xcb_connection::get() const
{
    return p_connection;
}

std::uint32_t xcb_connection::generate_id() const
{
    return xcb_generate_id(p_connection);
}

xcb_screen xcb_connection::get_screen(int num) const
{
    xcb_screen_iterator_t iter = xcb_setup_roots_iterator(p_setup);
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

}
