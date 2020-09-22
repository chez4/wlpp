#include <wlpp/xcb/xcb_window.hpp>

#include <memory>
#include <utility>

#include <xcb/xcb.h>

#include <wlpp/xcb/xcb_connection.hpp>

namespace wlpp {

xcb_window::xcb_window(std::shared_ptr<xcb_connection> server)
    : window()
    , server(std::move(server))
{
    *window = server->generate_id();
}

xcb_window::~xcb_window()
{
    xcb_destroy_window(server->get(), *window);
}

xcb_window::xcb_window(xcb_window &&other) noexcept
    : window(other.window)
{
    other.window = nullptr;
}

xcb_window &xcb_window::operator=(xcb_window other)
{
    if (this == &other) swap(*this, other);
    return *this;
}

void swap(xcb_window &a, xcb_window &b)
{
    std::swap(a.window, b.window);
}

}
