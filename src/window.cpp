#include <memory>
#include <utility>

#include <xcb/xcb.h>

#include "../include/wlpp/connection.hpp"
#include "../include/wlpp/window.hpp"

namespace wlpp {

window::window(std::shared_ptr<connection> server)
    : p_window()
    , server(std::move(server))
{
    *p_window = server->generate_id();
}

window::~window()
{
    //xcb_destroy_window();
}

window::window(window &&other) noexcept
    : p_window(other.p_window)
{
    other.p_window = nullptr;
}

window &window::operator=(window other)
{
    if (this == &other) swap(*this, other);
    return *this;
}

void swap(window &a, window &b)
{
    std::swap(a.p_window, b.p_window);
}

}
