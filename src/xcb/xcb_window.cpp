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
    , quit(false)
{
    wind = this->server->generate_id();

    std::uint32_t mask[2] = { screen.get_black_pixel(), XCB_EVENT_MASK_EXPOSURE }; // Change
    xcb_create_window(this->server->get(), XCB_COPY_FROM_PARENT, wind, screen.get_parent_window(), x, y, width, height, border_width, XCB_WINDOW_CLASS_INPUT_OUTPUT, screen.get_parent_visual(), XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK, mask);

    this->server->register_window(this);
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

    server->unregister_window(this);
}

xcb_window::xcb_window(xcb_window &&other) noexcept
    : wind(other.wind)
    , server(std::move(other.server))
    , quit(other.quit)
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
    std::swap(a.quit, b.quit);
}

xcb_window_t xcb_window::get() const
{
    return wind;
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
    return quit;
}

void xcb_window::key_press_event(std::uint8_t)
{
}

void xcb_window::key_release_event(std::uint8_t)
{
}

void xcb_window::button_press_event(std::uint8_t)
{
}

void xcb_window::button_release_event(std::uint8_t)
{
}

void xcb_window::motion_notify_event(std::uint8_t)
{
}

void xcb_window::enter_notify_event()
{
}

void xcb_window::leave_notify_event()
{
}

void xcb_window::focus_in_event()
{
}

void xcb_window::focus_out_event()
{
}

void xcb_window::expose_event(std::uint16_t, std::uint16_t, std::uint16_t, std::uint16_t)
{
}

void xcb_window::visibility_notify_event()
{
}

void xcb_window::create_notify_event(std::uint16_t, std::uint16_t, std::uint16_t, std::uint16_t)
{
}

void xcb_window::destroy_notify_event()
{
    quit = true;
}

void xcb_window::unmap_notify_event()
{
}

void xcb_window::map_notify_event()
{
}

void xcb_window::map_request_event()
{
}

void xcb_window::reparent_notify_event()
{
}

void xcb_window::configure_notify_event(std::uint16_t, std::uint16_t, std::uint16_t, std::uint16_t)
{
}

void xcb_window::configure_request_event()
{
}

void xcb_window::gravity_notify_event()
{
}

void xcb_window::resize_request_event(std::uint16_t, std::uint16_t)
{
}

void xcb_window::circulate_notify_event()
{
}

void xcb_window::circulate_request_event()
{
}

void xcb_window::property_notify_event()
{
}

void xcb_window::selection_clear_event()
{
}

void xcb_window::selection_request_event()
{
}

void xcb_window::selection_notify_event()
{
}

void xcb_window::colormap_notify_event()
{
}

void xcb_window::client_message_event()
{
}

}
