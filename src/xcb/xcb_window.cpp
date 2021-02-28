// Copyright (C) 2020-2021 Max Burns
// See LICENSE for more information
// wlpp   - src/xcb/xcb_window.cpp
// Author - chez4 20/09/2020

#include <wlpp/xcb/xcb_window.hpp>

#include <memory>
#include <utility>

#include <wlpp/xcb/xcb_connection.hpp>

namespace wlpp {

xcb_window::xcb_window(std::shared_ptr<xcb_connection> conn, int width, int height, int x, int y, const std::string &title)
    : conn(std::move(conn))
    , wind(this->conn->generate_id())
    , screen(this->conn->get_preffered_screen())
{
    ::xcb_create_window(this->conn->get(), XCB_COPY_FROM_PARENT, wind, screen.root, x, y, width, height, 0, XCB_WINDOW_CLASS_INPUT_OUTPUT, screen.root_visual, 0, nullptr);
    set_title(title);
}

xcb_window::xcb_window(std::shared_ptr<xcb_connection> conn, int width, int height, const std::string &title)
    : xcb_window(std::move(conn), width, height, 0, 0, title)
{
}

xcb_window::xcb_window(std::shared_ptr<xcb_connection> conn, const std::string &title)
    : xcb_window(std::move(conn), 800, 600, 0, 0, title)
{
}

xcb_window::~xcb_window()
{
    if (conn != nullptr) ::xcb_destroy_window(conn->get(), wind);
}

xcb_window::xcb_window(xcb_window &&other) noexcept
    : conn(std::move(other.conn))
    , wind(other.wind)
    , screen(other.screen)
{
    other.conn = nullptr;
}

xcb_window &xcb_window::operator=(xcb_window other)
{
    if (this != &other) swap(*this, other);
    return *this;
}

void swap(xcb_window &a, xcb_window &b)
{
    std::swap(a.conn, b.conn);
    std::swap(a.wind, b.wind);
    std::swap(a.screen, b.screen);
}

void xcb_window::set_title(const std::string &title) const
{
    xcb_change_property(conn->get(), XCB_PROP_MODE_REPLACE, wind, XCB_ATOM_WM_NAME, XCB_ATOM_STRING, 8, title.length(), title.c_str());
}

void xcb_window::show() const
{
    ::xcb_map_window(conn->get(), wind);
}

void xcb_window::hide() const
{
    ::xcb_unmap_window(conn->get(), wind);
}

bool xcb_window::has_quit() const
{
    return false;
}

}
