#include <utility>

#include <cstdint>

#include <xcb/xcb.h>

#include "../include/wlpp/connection.hpp"
#include "../include/wlpp/screen.hpp"

namespace wlpp {

connection::connection()
{
    p_connection = xcb_connect(nullptr, p_screen_pref);

    p_setup = xcb_get_setup(p_connection);
}

connection::~connection()
{
    if (p_connection != nullptr) {
        xcb_disconnect(p_connection);
    }
}

connection::connection(connection &&other) noexcept
    : p_connection(other.p_connection)
    , p_screen_pref(other.p_screen_pref)
    , p_setup(other.p_setup)
{
    other.p_connection = nullptr;
    other.p_screen_pref = nullptr;
    other.p_setup = nullptr;
}

connection &connection::operator=(connection other)
{
    if (this != &other) swap(*this, other);
    return *this;
}

void swap(connection &a, connection &b)
{
    std::swap(a.p_connection, b.p_connection);
    std::swap(a.p_screen_pref, b.p_screen_pref);
    std::swap(a.p_setup, b.p_setup);
}

std::uint32_t connection::generate_id() const
{
    return xcb_generate_id(p_connection);
}

screen connection::get_screen(int num) const
{
    xcb_screen_iterator_t iter = xcb_setup_roots_iterator(p_setup);
    xcb_screen_next(&iter);
}

}
