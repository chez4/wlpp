/*
 * wlpp Copyright 2020 Max Burns
 * See LICENSE for more information.
 */

#include <wlpp/xcb/xcb_screen.hpp>

#include <xcb/xcb.h>

namespace wlpp {

xcb_screen::xcb_screen(const xcb_screen_t &screen)
    : screen(screen)
{
}

xcb_window_t xcb_screen::get_parent_window() const
{
    return screen.root;
}

xcb_visualid_t xcb_screen::get_parent_visual() const
{
    return screen.root_visual;
}

std::uint32_t xcb_screen::get_white_pixel() const
{
    return screen.white_pixel;
}

std::uint32_t xcb_screen::get_black_pixel() const
{
    return screen.black_pixel;
}

}
