#include <utility>

#include <cstdint>

#include <xcb/xcb.h>

#include "../../include/wlpp/xcb/xcb_connection.hpp"
#include "../../include/wlpp/xcb/xcb_screen.hpp"

namespace wlpp {

xcb_connection::xcb_connection()
{
    connection = xcb_connect(nullptr, screen_pref);

    setup = xcb_get_setup(connection);
}

xcb_connection::~xcb_connection()
{
    if (connection != nullptr) {
        xcb_disconnect(connection);
    }
}

xcb_connection::xcb_connection(xcb_connection &&other) noexcept
    : connection(other.connection)
    , screen_pref(other.screen_pref)
    , setup(other.setup)
{
    other.connection = nullptr;
    other.screen_pref = nullptr;
    other.setup = nullptr;
}

xcb_connection &xcb_connection::operator=(xcb_connection other)
{
    if (this != &other) swap(*this, other);
    return *this;
}

void swap(xcb_connection &a, xcb_connection &b)
{
    std::swap(a.connection, b.connection);
    std::swap(a.screen_pref, b.screen_pref);
    std::swap(a.setup, b.setup);
}

std::uint32_t xcb_connection::generate_id() const
{
    return xcb_generate_id(connection);
}

xcb_screen xcb_connection::get_screen(int num) const
{
    xcb_screen_iterator_t iter = xcb_setup_roots_iterator(setup);
    xcb_screen_next(&iter);
}

}
