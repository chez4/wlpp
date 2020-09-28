/*
 * wlpp Copyright 2020 Max Burns
 * See LICENSE for more information.
 */

#include <wlpp/xcb/xcb_window.hpp>

#include <memory>
#include <utility>

#include <cstdint>

#include <xcb/xcb.h>

#include <wlpp/xcb/xcb_connection.hpp>
#include <wlpp/xcb/xcb_screen.hpp>

namespace wlpp {

xcb_window::xcb_window(std::shared_ptr<xcb_connection> server, const xcb_screen &screen, std::uint16_t x, std::uint16_t y, std::uint16_t width, std::uint16_t height, std::uint16_t border_width)
    : wind()
    , server(std::move(server))
{
    wind = this->server->generate_id();
    xcb_create_window(this->server->get(), XCB_COPY_FROM_PARENT, wind, screen.get_parent_window(), x, y, width, height, border_width, XCB_WINDOW_CLASS_INPUT_OUTPUT, screen.get_parent_visual(), 0, nullptr);
}

xcb_window::xcb_window(std::shared_ptr<xcb_connection> server, const xcb_screen &screen, std::uint16_t x, std::uint16_t y, std::uint16_t width, std::uint16_t height)
    : xcb_window(std::move(server), screen, x, y, width, height, 0)
{
}

xcb_window::xcb_window(std::shared_ptr<xcb_connection> server, const xcb_screen &screen, std::uint16_t width, std::uint16_t height)
    : xcb_window(std::move(server), screen, 0, 0, width, height, 0)
{
}

xcb_window::~xcb_window()
{
    xcb_destroy_window(server->get(), wind);
}

xcb_window::xcb_window(xcb_window &&other) noexcept
    : wind(other.wind)
    , server(std::move(other.server))
{
}

xcb_window &xcb_window::operator=(xcb_window other)
{
    if (this != &other) swap(*this, other);
    return *this;
}

void swap(xcb_window &a, xcb_window &b)
{
    std::swap(a.wind, b.wind);
    std::swap(a.server, b.server);
}

xcb_window_t xcb_window::get() const
{
    return wind;
}

void xcb_window::poll_events() const
{

}

void xcb_window::wait_events() const
{
}

void xcb_window::show() const
{
    server->map_window(*this);
}

void xcb_window::hide() const
{
    server->unmap_window(*this);
}

bool xcb_window::has_closed() const
{
    return false;
}

}
